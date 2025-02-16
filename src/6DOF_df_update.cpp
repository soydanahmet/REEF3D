/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2022 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
--------------------------------------------------------------------*/

#include"6DOF_df_object.h"
#include"lexer.h"
#include"fdm.h"
#include"ghostcell.h"

void sixdof_df_object::updateFSI(lexer *p, fdm *a, ghostcell* pgc, bool finalise)
{
    // Print quaternion
	if(p->mpirank==0)
    {
		//cout<<"Quaternion: "<<e_(0)<<" "<<e_(1)<<" "<<e_(2)<<" "<<e_(3)<<endl;
    }
	
    // Update transformation matrix (Shivarama PhD thesis, p. 19)
    quat_matrices(e_);

    // Calculate new position
    updatePosition(p, a, pgc, finalise);

    // Update angular velocities 
    omega_B = I_.inverse()*h_;
    omega_I = R_*omega_B;
      
    // Global body variables
    interface(p,false);    
    maxvel(p,a,pgc);
}


void sixdof_df_object::updatePosition(lexer *p, fdm *a, ghostcell *pgc, bool finalise)
{
	// Calculate Euler angles from quaternion
	
	// around z-axis
	psi = atan2(2.0*(e_(1)*e_(2) + e_(3)*e_(0)), 1.0 - 2.0*(e_(2)*e_(2) + e_(3)*e_(3))); 
	
	// around new y-axis
	double arg = 2.0*(e_(0)*e_(2) - e_(1)*e_(3));
	
	if (fabs(arg) >= 1.0)
	{
		theta = SIGN(arg)*PI/2.0;
	}
	else
	{
		theta = asin(arg);														
	}	
		
	// around new x-axis
	phi = atan2(2.0*(e_(2)*e_(3) + e_(1)*e_(0)), 1.0 - 2.0*(e_(1)*e_(1) + e_(2)*e_(2)));

	if(p->mpirank==0 && finalise == true)
    {
        cout<<"XG: "<<c_(0)<<" YG: "<<c_(1)<<" ZG: "<<c_(2)<<" phi: "<<phi*(180.0/PI)<<" theta: "<<theta*(180.0/PI)<<" psi: "<<psi*(180.0/PI)<<endl;
		cout<<"Ue: "<<p_(0)/Mass_fb<<" Ve: "<<p_(1)/Mass_fb<<" We: "<<p_(2)/Mass_fb<<" Pe: "<<omega_I(0)<<" Qe: "<<omega_I(1)<<" Re: "<<omega_I(2)<<endl;
    }

	// Update position of triangles 
	for(n=0; n<tricount; ++n)
	{
        for(int q=0; q<3; q++)
        {
            // Update coordinates of triangles 
            // (tri_x0 is vector between tri_x and xg)
  
            Eigen::Vector3d point(tri_x0[n][q], tri_y0[n][q], tri_z0[n][q]);
					
            point = R_*point;
        
            tri_x[n][q] = point(0) + c_(0);
            tri_y[n][q] = point(1) + c_(1);
            tri_z[n][q] = point(2) + c_(2);

			// 2D
			if(p->X11_v != 1 && p->X11_p != 1 && p->X11_r != 1) 
			{
				tri_y[n][q] = tri_y0[n][q] + c_(1);	
			}
        }

	}
	
    // Update floating level set function
	ray_cast(p,a,pgc);
	reini_AB2(p,a,pgc,a->fb);
    pgc->start4a(p,a->fb,50);   
}

void sixdof_df_object::updateForcing(lexer *p, fdm *a, ghostcell *pgc, double alpha,
                                     field& uvel, field& vvel, field& wvel,field1& fx, field2& fy, field3& fz)
{
    // Determine floating body velocities
    Eigen::Matrix<double, 6, 1> u_fb;
    
    if (p->knoy == 1)
    {
        u_fb << p_(0)/Mass_fb, 0.0, p_(2)/Mass_fb, 0.0, omega_I(1), 0.0;
    }
    else
    {
        u_fb << p_(0)/Mass_fb, p_(1)/Mass_fb, p_(2)/Mass_fb, omega_I(0), omega_I(1), omega_I(2);
    }

    // Calculate forcing fields
    double H, uf, vf, wf;


    ULOOP
    {
        uf = u_fb(0) + u_fb(4)*(p->pos1_z() - c_(2)) - u_fb(5)*(p->pos1_y() - c_(1));
        H = Hsolidface(p,a,1,0,0);
       
        fx(i,j,k) += H*(uf - uvel(i,j,k))/(alpha*p->dt);   
        a->fbh1(i,j,k) = min(a->fbh1(i,j,k) + H, 1.0); 
    }
    VLOOP
    {
        vf = u_fb(1) + u_fb(5)*(p->pos2_x() - c_(0)) - u_fb(3)*(p->pos2_z() - c_(2));
        H = Hsolidface(p,a,0,1,0);
       
        fy(i,j,k) += H*(vf - vvel(i,j,k))/(alpha*p->dt);
        a->fbh2(i,j,k) = min(a->fbh2(i,j,k) + H, 1.0); 
    }
    WLOOP
    {
        wf = u_fb(2) + u_fb(3)*(p->pos3_y() - c_(1)) - u_fb(4)*(p->pos3_x() - c_(0));
        H = Hsolidface(p,a,0,0,1);

        fz(i,j,k) += H*(wf - wvel(i,j,k))/(alpha*p->dt);
        a->fbh3(i,j,k) = min(a->fbh3(i,j,k) + H, 1.0); 
    }
    LOOP
    {
        H = Hsolidface(p,a,0,0,0);
        a->fbh4(i,j,k) = min(a->fbh4(i,j,k) + H, 1.0); 
    }

    pgc->start1(p,a->fbh1,10);
    pgc->start2(p,a->fbh2,11);
    pgc->start3(p,a->fbh3,12);
    pgc->start4(p,a->fbh4,40);

    pgc->start1(p,fx,10);
    pgc->start2(p,fy,11);
    pgc->start3(p,fz,12);         
};

void sixdof_df_object::quat_matrices(const Eigen::Vector4d& e)
{
    E_ << -e(1), e(0), -e(3), e(2),
         -e(2), e(3), e(0), -e(1),
         -e(3), -e(2), e(1), e(0); 

    G_ << -e(1), e(0), e(3), -e(2),
         -e(2), -e(3), e(0), e(1),
         -e(3), e(2), -e(1), e(0); 

    R_ = E_*G_.transpose(); 
    Rinv_ = R_.inverse();

    quatRotMat = R_;
}


double sixdof_df_object::Hsolidface(lexer *p, fdm *a, int aa, int bb, int cc)
{
    double psi, H, phival_fb;
	
    psi = p->X41*(1.0/3.0)*(p->DXN[IP]+p->DYN[JP]+p->DZN[KP]);

    if (p->knoy == 1)
    {
        psi = p->X41*(1.0/2.0)*(p->DXN[IP] + p->DZN[KP]); 
    }

    // Construct solid heaviside function

    phival_fb = 0.5*(a->fb(i,j,k) + a->fb(i+aa,j+bb,k+cc));
    
    if (-phival_fb > psi)
    {
        H = 1.0;
    }
    else if (-phival_fb < -psi)
    {
        H = 0.0;
    }
    else
    {
        H = 0.5*(1.0 + -phival_fb/psi + (1.0/PI)*sin((PI*-phival_fb)/psi));
    }
        
    return H;
}
