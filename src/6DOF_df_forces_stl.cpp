/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2021 Hans Bihs

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
#include <math.h>

void sixdof_df_object::forces_stl
(
    lexer* p, fdm *a, ghostcell *pgc, double alpha,
    field& uvel, field& vvel, field& wvel
)
{
	double x0,x1,x2,y0,y1,y2,z0,z1,z2;
	double xc,yc,zc;
	double at,bt,ct,st;
	double nx,ny,nz,norm;
	double A_triang,A;
	double p_int,rho_int,nu_int,enu_int,u_int,v_int,w_int;
	double du,dv,dw, dudx, dudy, dudz, dvdx, dvdy, dvdz, dwdx, dwdy, dwdz;
	double dudxf, dudyf, dudzf, dvdxf, dvdyf, dvdzf, dwdxf, dwdyf, dwdzf;
	double dudxb, dudyb, dudzb, dvdxb, dvdyb, dvdzb, dwdxb, dwdyb, dwdzb;
	double xlocvel,ylocvel,zlocvel,xlocp,ylocp,zlocp;
	double Fx,Fy,Fz,Fp_x,Fp_y,Fp_z,Fv_x,Fv_y,Fv_z;
    double Xe_p,Ye_p,Ze_p,Xe_v,Ye_v,Ze_v;

    A=0.0;
    Xe=Ye=Ze=Ke=Me=Ne=0.0;
    Xe_p=Ye_p=Ze_p=Xe_v=Ye_v=Ze_v=0.0;

    for (int n = 0; n < tricount; ++n)
    {     
		// Vertices of triangle
	
		x0 = tri_x[n][0];
		x1 = tri_x[n][1];
		x2 = tri_x[n][2];
		
		y0 = tri_y[n][0];
		y1 = tri_y[n][1];
		y2 = tri_y[n][2];
		
		z0 = tri_z[n][0];
		z1 = tri_z[n][1];
		z2 = tri_z[n][2];  
           
		   
		// Center of triangle
		
		xc = (x0 + x1 + x2)/3.0;
		yc = (y0 + y1 + y2)/3.0;
		zc = (z0 + z1 + z2)/3.0;
            
		if 
		(
			xc >= p->originx && xc < p->endx &&
			yc >= p->originy && yc < p->endy &&
			zc >= p->originz && zc < p->endz
		)
		{
			// Area of triangle using Heron's formula

			at = sqrt(pow(x1-x0,2.0) + pow(y1-y0,2.0) + pow(z1-z0,2.0));
			bt = sqrt(pow(x1-x2,2.0) + pow(y1-y2,2.0) + pow(z1-z2,2.0));
			ct = sqrt(pow(x2-x0,2.0) + pow(y2-y0,2.0) + pow(z2-z0,2.0));
				
			st = 0.5*(at+bt+ct);
				
			A_triang = sqrt(MAX(0.0,st*(st-at)*(st-bt)*(st-ct)));
				

			// Normal vectors (always pointing outwards)      
				
			nx = (y1 - y0) * (z2 - z0) - (y2 - y0) * (z1 - z0);
			ny = (x2 - x0) * (z1 - z0) - (x1 - x0) * (z2 - z0); 
			nz = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);

			norm = sqrt(nx*nx + ny*ny + nz*nz);
			
			nx /= norm > 1.0e-20 ? norm : 1.0e20;
			ny /= norm > 1.0e-20 ? norm : 1.0e20;
			nz /= norm > 1.0e-20 ? norm : 1.0e20;

            xlocp = xc + p->X42*nx*p->DXP[IP];
			ylocp = yc + p->X42*ny*p->DYP[JP];
			zlocp = zc + p->X42*nz*p->DZP[KP];

			// Add normal stress contributions

			p_int = p->ccipol4_a(a->press,xlocp,ylocp,zlocp);
			
			Fp_x = -nx*p_int*A_triang;
			Fp_y = -ny*p_int*A_triang;
            Fp_z = -nz*p_int*A_triang;
		
		   
             // Add tangential stress contributions

             xlocvel = xc + nx*p->DXP[IP];
             ylocvel = yc + ny*p->DYP[JP];
             zlocvel = zc + nz*p->DZP[KP];
/*
             double xlocvelp1 = xlocvel + p->DXP[IP];
             double ylocvelp1 = ylocvel + p->DYP[JP];
             double zlocvelp1 = zlocvel + p->DZP[KP];
             double upx1 = p->ccipol1_a(uvel,xlocvelp1,ylocvel,zlocvel);
             double upy1 = p->ccipol1_a(uvel,xlocvel,ylocvelp1,zlocvel);
             double upz1 = p->ccipol1_a(uvel,xlocvel,ylocvel,zlocvelp1);
             double vpx1 = p->ccipol2_a(vvel,xlocvelp1,ylocvel,zlocvel);
             double vpy1 = p->ccipol2_a(vvel,xlocvel,ylocvelp1,zlocvel);
             double vpz1 = p->ccipol2_a(vvel,xlocvel,ylocvel,zlocvelp1);
             double wpx1 = p->ccipol3_a(wvel,xlocvelp1,ylocvel,zlocvel);
             double wpy1 = p->ccipol3_a(wvel,xlocvel,ylocvelp1,zlocvel);
             double wpz1 = p->ccipol3_a(wvel,xlocvel,ylocvel,zlocvelp1);
             double nu_xp1 = p->ccipol4_a(a->visc,xlocvelp1,ylocvel,zlocvel);
             double nu_yp1 = p->ccipol4_a(a->visc,xlocvel,ylocvelp1,zlocvel);
             double nu_zp1 = p->ccipol4_a(a->visc,xlocvel,ylocvel,zlocvelp1);
             double enu_xp1 = p->ccipol4_a(a->eddyv,xlocvelp1,ylocvel,zlocvel);
             double enu_yp1 = p->ccipol4_a(a->eddyv,xlocvel,ylocvelp1,zlocvel);
             double enu_zp1 = p->ccipol4_a(a->eddyv,xlocvel,ylocvel,zlocvelp1);
             double rho_xp1 = p->ccipol4_a(a->ro,xlocvelp1,ylocvel,zlocvel);
             double rho_yp1 = p->ccipol4_a(a->ro,xlocvel,ylocvelp1,zlocvel);
             double rho_zp1 = p->ccipol4_a(a->ro,xlocvel,ylocvel,zlocvelp1);

             double xlocvelm1 = xlocvel - p->DXP[IP];
             double ylocvelm1 = ylocvel - p->DYP[JP];
             double zlocvelm1 = zlocvel - p->DZP[KP];
             double umx1 = p->ccipol1_a(uvel,xlocvelm1,ylocvel,zlocvel);
             double umy1 = p->ccipol1_a(uvel,xlocvel,ylocvelm1,zlocvel);
             double umz1 = p->ccipol1_a(uvel,xlocvel,ylocvel,zlocvelm1);
             double vmx1 = p->ccipol2_a(vvel,xlocvelm1,ylocvel,zlocvel);
             double vmy1 = p->ccipol2_a(vvel,xlocvel,ylocvelm1,zlocvel);
             double vmz1 = p->ccipol2_a(vvel,xlocvel,ylocvel,zlocvelm1);
             double wmx1 = p->ccipol3_a(wvel,xlocvelm1,ylocvel,zlocvel);
             double wmy1 = p->ccipol3_a(wvel,xlocvel,ylocvelm1,zlocvel);
             double wmz1 = p->ccipol3_a(wvel,xlocvel,ylocvel,zlocvelm1);
             double nu_xm1 = p->ccipol4_a(a->visc,xlocvelm1,ylocvel,zlocvel);
             double nu_ym1 = p->ccipol4_a(a->visc,xlocvel,ylocvelm1,zlocvel);
             double nu_zm1 = p->ccipol4_a(a->visc,xlocvel,ylocvel,zlocvelm1);
             double enu_xm1 = p->ccipol4_a(a->eddyv,xlocvelm1,ylocvel,zlocvel);
             double enu_ym1 = p->ccipol4_a(a->eddyv,xlocvel,ylocvelm1,zlocvel);
             double enu_zm1 = p->ccipol4_a(a->eddyv,xlocvel,ylocvel,zlocvelm1);
             double rho_xm1 = p->ccipol4_a(a->ro,xlocvelm1,ylocvel,zlocvel);
             double rho_ym1 = p->ccipol4_a(a->ro,xlocvel,ylocvelm1,zlocvel);
             double rho_zm1 = p->ccipol4_a(a->ro,xlocvel,ylocvel,zlocvelm1);

             dudx = (rho_xp1*(nu_xp1+enu_xp1)*upx1 - rho_xm1*(nu_xm1+enu_xm1)*umx1)/(2.0*p->DXP[IP]);
             dudy = (rho_yp1*(nu_yp1+enu_yp1)*upy1 - rho_ym1*(nu_ym1+enu_ym1)*umy1)/(2.0*p->DYP[JP]);
             dudy = (rho_zp1*(nu_zp1+enu_zp1)*upz1 - rho_zm1*(nu_zm1+enu_zm1)*umz1)/(2.0*p->DZP[KP]);

             dvdx = (rho_xp1*(nu_xp1+enu_xp1)*vpx1 - rho_xm1*(nu_xm1+enu_xm1)*vmx1)/(2.0*p->DXP[IP]);
             dvdy = (rho_yp1*(nu_yp1+enu_yp1)*vpy1 - rho_ym1*(nu_ym1+enu_ym1)*vmy1)/(2.0*p->DYP[JP]);
             dvdy = (rho_zp1*(nu_zp1+enu_zp1)*vpz1 - rho_zm1*(nu_zm1+enu_zm1)*vmz1)/(2.0*p->DZP[KP]);

             dwdx = (rho_xp1*(nu_xp1+enu_xp1)*wpx1 - rho_xm1*(nu_xm1+enu_xm1)*wmx1)/(2.0*p->DXP[IP]);
             dwdy = (rho_yp1*(nu_yp1+enu_yp1)*wpy1 - rho_ym1*(nu_ym1+enu_ym1)*wmy1)/(2.0*p->DYP[JP]);
             dwdy = (rho_zp1*(nu_zp1+enu_zp1)*wpz1 - rho_zm1*(nu_zm1+enu_zm1)*wmz1)/(2.0*p->DZP[KP]);

             Fv_x = A_triang*(2.0*dudx*nx + (dudy + dvdx)*ny + (dudz + dwdx)*nz);
             Fv_y = A_triang*((dudy + dvdx)*nx + 2.0*dvdy*ny + (dvdz + dwdy)*nz);
             Fv_z = A_triang*((dudz + dwdx)*nx + (dvdz + dwdy)*ny + 2.0*dwdz*nz);
*/



			nu_int = p->ccipol4_a(a->visc,xlocvel,ylocvel,zlocvel);
			enu_int = 0.0; //p->ccipol4_a(a->eddyv,xlocvel,ylocvel,zlocvel);
			rho_int = p->ccipol4_a(a->ro,xlocvel,ylocvel,zlocvel);
			
            // Central differences                                 
	        
            i = p->posc_i(xlocvel);
			j = p->posc_j(ylocvel);
			k = p->posc_k(zlocvel);
            
            dudx = (uvel(i+1,j,k) - uvel(i-1,j,k))/(p->DXP[IP] + p->DXP[IM1]);
            dudy = (uvel(i,j+1,k) - uvel(i,j-1,k))/(p->DYP[JP] + p->DYP[JM1]);
            dudz = (uvel(i,j,k+1) - uvel(i,j,k-1))/(p->DZP[KP] + p->DZP[KM1]);
                                                                           
            dvdx = (vvel(i+1,j,k) - vvel(i-1,j,k))/(p->DXP[IP] + p->DXP[IM1]);
            dvdy = (vvel(i,j+1,k) - vvel(i,j-1,k))/(p->DYP[JP] + p->DYP[JM1]);
            dvdz = (vvel(i,j,k+1) - vvel(i,j,k-1))/(p->DZP[KP] + p->DZP[KM1]);
                                                                            
            dwdx = (wvel(i+1,j,k) - wvel(i-1,j,k))/(p->DXP[IP] + p->DXP[IM1]);
            dwdy = (wvel(i,j+1,k) - wvel(i,j-1,k))/(p->DYP[JP] + p->DYP[JM1]);
            dwdz = (wvel(i,j,k+1) - wvel(i,j,k-1))/(p->DZP[KP] + p->DZP[KM1]);

            Fv_x = rho_int*(nu_int + enu_int)*A_triang*(2.0*dudx*nx + (dudy + dvdx)*ny + (dudz + dwdx)*nz);
            Fv_y = rho_int*(nu_int + enu_int)*A_triang*((dudy + dvdx)*nx + 2.0*dvdy*ny + (dvdz + dwdy)*nz);
            Fv_z = rho_int*(nu_int + enu_int)*A_triang*((dudz + dwdx)*nx + (dvdz + dwdy)*ny + 2.0*dwdz*nz);


            // Total forces
            
            Fx = Fp_x + Fv_x;
            Fy = Fp_y + Fv_y;
            Fz = Fp_z + Fv_z;
            

			// Add forces to global forces
			
			Xe += Fx;
			Ye += Fy;
			Ze += Fz;

			Ke += (yc - c_(1))*Fz - (zc - c_(2))*Fy;
			Me += (zc - c_(2))*Fx - (xc - c_(0))*Fz;
			Ne += (xc - c_(0))*Fy - (yc - c_(1))*Fx;
            
            Xe_p += Fp_x;
            Ye_p += Fp_y;
            Ze_p += Fp_z;
            
            Xe_v += Fv_x;
            Ye_v += Fv_y;
            Ze_v += Fv_z;
							
			A += A_triang;
		}
	}		
 
	// Communication with other processors
	
    A = pgc->globalsum(A);
	
	Xe = pgc->globalsum(Xe);
	Ye = pgc->globalsum(Ye);
	Ze = pgc->globalsum(Ze);
	Ke = pgc->globalsum(Ke);
	Me = pgc->globalsum(Me);
	Ne = pgc->globalsum(Ne);

	Xe_p = pgc->globalsum(Xe_p);
	Ye_p = pgc->globalsum(Ye_p);
	Ze_p = pgc->globalsum(Ze_p);
	Xe_v = pgc->globalsum(Xe_v);
	Ye_v = pgc->globalsum(Ye_v);
	Ze_v = pgc->globalsum(Ze_v);

	// Add gravity force
	
	Xe += a->gi*Mass_fb;
	Ye += a->gj*Mass_fb;
	Ze += a->gk*Mass_fb;


    // Print results
	
    if (p->mpirank == 0 && alpha == 1.0) 
    {
        ofstream print;
        char str[1000];
       
        if(p->P14==0)
        sprintf(str,"REEF3D_6DOF_forces_%i.dat",n6DOF);
        if(p->P14==1)
        sprintf(str,"./REEF3D_CFD_6DOF/REEF3D_6DOF_forces_%i.dat",n6DOF);

        print.open(str, std::ofstream::out | std::ofstream::app);
        print<<p->simtime<<" \t "<<Xe<<" \t "<<Ye<<" \t "<<Ze<<" \t "<<Ke
        <<" \t "<<Me<<" \t "<<Ne<<" \t "<<Xe_p<<" \t "<<Ye_p<<" \t "<<Ze_p<<" \t "<<Xe_v<<" \t "<<Ye_v<<" \t "<<Ze_v<<endl;   
        print.close();
    }

	if (p->mpirank == 0)
	{
		cout<<"Xe: "<<Xe<<" Ye: "<<Ye<<" Ze: "<<Ze<<" Ke: "<<Ke<<" Me: "<<Me<<" Ne: "<<Ne<<endl;
	}


    // Save dynamic pressure
/*    LOOP
    {
        a->test(i,j,k) = a->press(i,j,k) + a->ro(i,j,k)*a->gk*p->pos_z();
    }
    pgc->start4(p,a->test,40);
*/
}
