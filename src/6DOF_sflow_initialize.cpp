/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2022 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
--------------------------------------------------------------------*/

#include"6DOF_sflow.h"
#include"lexer.h"
#include"fdm.h"
#include"fdm2D.h"
#include"ghostcell.h"
#include"vrans.h"
   

void sixdof_sflow::initialize(lexer *p, fdm *a, ghostcell *pgc, vector<net*>& pnet)
{
}
    
void sixdof_sflow::ini(lexer *p, fdm2D *b, ghostcell *pgc)
{
    // Initialise parameters
	ini_parameter(p,b,pgc);
    
    // Initialise folder structure
	print_ini(p,b,pgc);
    
    // Initialise object 
    if (p->X400 == 1)
    {
        cylinder(p,b,pgc);
    }
    else if (p->X400 == 2)
    {
        box(p,b,pgc);
    }
    else
    {
         cout<<"Missing object, define X 110 or X 133 according to X 401"<<endl;
    }
    //geometry_refinement(p);

    // Initialise position of bodies
    iniPosition_RBM(p,b,pgc);

    // Initialise distance field
	ray_cast(p,b,pgc);
    time_preproc(p); 
	reini(p,pgc,fb);

    SLICELOOP4
    {
        b->test(i,j) = fb(i,j);
    }
    pgc->gcsl_start4(p,b->test,50);
    
    // Print initial body 
    print_stl(p,pgc);
}



void sixdof_sflow::ini_parameter(lexer *p, fdm2D *b, ghostcell *pgc)
{
    // Prescribed motions
    Uext = Vext = Wext = Pext = Qext = Rext = 0.0; 
    
    if (p->X210 == 1)
    {
        Uext = p->X210_u;
        Vext = p->X210_v;
        Wext = p->X210_w;
    }
    if (p->X211 == 1)
    {
        Pext = p->X211_p;
        Qext = p->X211_q;
        Rext = p->X211_r;
    }
    if (p->X221==1)
    {
        //motion_vec(p,a,pgc);
        cout<<"not implemented yet"<<endl;
    }

    // Position
    p->ufbi=p->vfbi=p->wfbi=0.0;
	p->pfbi=p->qfbi=p->rfbi=0.0;
    phi = theta = psi = 0.0;
    quatRotMat << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
    
    if(p->X23==1)
    {
        p->xg = p->X23_x; 
        p->yg = p->X23_y; 
        p->zg = p->X23_z; 
    }
    else
    {
         cout<<"Please provide centre of floating body using X 23!"<<endl;
    }

	
    // Printing
    printtime = 0.0;
    p->printcount_sixdof = 0;

    n6DOF = 0;
}

void sixdof_sflow::iniPosition_RBM(lexer *p, fdm2D *b, ghostcell *pgc)
{
    // Store initial position of triangles
	for(n=0; n<tricount; ++n)
	{
        for(int q=0; q<3; q++)
        {        
            tri_x0[n][q] = tri_x[n][q] - p->xg;
            tri_y0[n][q] = tri_y[n][q] - p->yg;
            tri_z0[n][q] = tri_z[n][q] - p->zg;
        }
    }
	
	// Initial rotation
	if (p->X101==1)
	{	
        phi = p->X101_phi*(PI/180.0);
        theta = p->X101_theta*(PI/180.0);
        psi = p->X101_psi*(PI/180.0);	
	
		for (n=0; n<tricount; ++n)
		{
			rotation_tri
				(p,-phi,-theta,-psi,tri_x[n][0],tri_y[n][0],tri_z[n][0],p->xg,p->yg,p->zg);
			rotation_tri
				(p,-phi,-theta,-psi,tri_x[n][1],tri_y[n][1],tri_z[n][1],p->xg,p->yg,p->zg);
			rotation_tri
				(p,-phi,-theta,-psi,tri_x[n][2],tri_y[n][2],tri_z[n][2],p->xg,p->yg,p->zg);
		}
	}
	
	// Initialise quaternions (Goldstein p. 604)
	e_(0) = 
		 cos(0.5*phi)*cos(0.5*theta)*cos(0.5*psi) 
		+ sin(0.5*phi)*sin(0.5*theta)*sin(0.5*psi);
	e_(1) = 
		 sin(0.5*phi)*cos(0.5*theta)*cos(0.5*psi) 
		- cos(0.5*phi)*sin(0.5*theta)*sin(0.5*psi);
	e_(2) = 
		 cos(0.5*phi)*sin(0.5*theta)*cos(0.5*psi) 
		+ sin(0.5*phi)*cos(0.5*theta)*sin(0.5*psi);
	e_(3) = 
		 cos(0.5*phi)*cos(0.5*theta)*sin(0.5*psi) 
		- sin(0.5*phi)*sin(0.5*theta)*cos(0.5*psi);   

    // Initialise rotation matrices
    quat_matrices(e_);
}


void sixdof_sflow::cylinder(lexer *p, fdm2D *b, ghostcell *pgc)
{
	double U,ds,angle;
	double xm,ym,zm,z1,z2,r;
	int snum, trisum;
	
	xm = p->X133_xc;
	ym = p->X133_yc;
    zm = p->X133_zc;
	z1 = zm - 0.5*p->X133_h;
	z2 = zm + 0.5*p->X133_h;
    r = p->X133_rad;

    // Prepare fields
    U = 2.0 * PI * r;
	ds = p->DXM;
	snum = int(U/ds);
    trisum=5*(snum+1);
    p->Darray(tri_x,trisum,3);
	p->Darray(tri_y,trisum,3);
	p->Darray(tri_z,trisum,3);
    p->Darray(tri_x0,trisum,3);
	p->Darray(tri_y0,trisum,3);
	p->Darray(tri_z0,trisum,3);    	

    // Vertices	
	ds = (2.0*PI)/double(snum);
	angle=0.0;
    tricount = 0;

	for(int n=0; n<snum; ++n)
	{
        //bottom circle	
        tri_x[tricount][0] = xm;
        tri_y[tricount][0] = ym;
        tri_z[tricount][0] = z1;
        
        tri_x[tricount][1] = xm + r*cos(angle);
        tri_y[tricount][1] = ym + r*sin(angle);
        tri_z[tricount][1] = z1;
        
        tri_x[tricount][2] = xm + r*cos(angle+ds);
        tri_y[tricount][2] = ym + r*sin(angle+ds);
        tri_z[tricount][2] = z1;
        ++tricount;
            
        //top circle
        tri_x[tricount][0] = xm;
        tri_y[tricount][0] = ym;
        tri_z[tricount][0] = z2;
        
        tri_x[tricount][1] = xm + r*cos(angle);
        tri_y[tricount][1] = ym + r*sin(angle);
        tri_z[tricount][1] = z2;
        
        tri_x[tricount][2] = xm + r*cos(angle+ds);
        tri_y[tricount][2] = ym + r*sin(angle+ds);
        tri_z[tricount][2] = z2;
        ++tricount;
        
        //side		
        // 1st triangle
        tri_x[tricount][0] = xm + r*cos(angle);
        tri_y[tricount][0] = ym + r*sin(angle);
        tri_z[tricount][0] = z1;
        
        tri_x[tricount][1] = xm + r*cos(angle+ds);
        tri_y[tricount][1] = ym + r*sin(angle+ds);
        tri_z[tricount][1] = z2;
        
        tri_x[tricount][2] = xm + r*cos(angle+ds);
        tri_y[tricount][2] = ym + r*sin(angle+ds);
        tri_z[tricount][2] = z1;
        ++tricount;
        
        // 2nd triangle
        tri_x[tricount][0] = xm + r*cos(angle);
        tri_y[tricount][0] = ym + r*sin(angle);
        tri_z[tricount][0] = z1;
        
        tri_x[tricount][1] = xm + r*cos(angle+ds);
        tri_y[tricount][1] = ym + r*sin(angle+ds);
        tri_z[tricount][1] = z2;
        
        tri_x[tricount][2] = xm + r*cos(angle);
        tri_y[tricount][2] = ym + r*sin(angle);
        tri_z[tricount][2] = z2;
        ++tricount;
            
        angle+=ds;
	}
}

void sixdof_sflow::box(lexer *p, fdm2D *b, ghostcell *pgc)
{
    // Prepare fields
    int trisum=12*p->X110;
    p->Darray(tri_x,trisum,3);
	p->Darray(tri_y,trisum,3);
	p->Darray(tri_z,trisum,3);
    p->Darray(tri_x0,trisum,3);
	p->Darray(tri_y0,trisum,3);
	p->Darray(tri_z0,trisum,3);    	

    tricount = 0;

    xs = p->X110_xs[0];
    xe = p->X110_xe[0];
	
    ys = p->X110_ys[0];
    ye = p->X110_ye[0];

    zs = p->X110_zs[0];
    ze = p->X110_ze[0];    
	
	// Face 3
	// Tri 1
	
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xe;

	tri_y[tricount][0] = ys;
	tri_y[tricount][1] = ys;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = zs;
	tri_z[tricount][1] = zs;
	tri_z[tricount][2] = ze;
	++tricount;

	// Tri 2
	tri_x[tricount][0] = xe;
	tri_x[tricount][1] = xs;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ys;
	tri_y[tricount][1] = ys;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = zs;
	++tricount;

	// Face 4
	// Tri 3
	tri_x[tricount][0] = xe;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xe;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ys;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = zs;
	++tricount;

	// Tri 4
	tri_x[tricount][0] = xe;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xe;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = zs;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = zs;
	++tricount;

	// Face 1
	// Tri 5
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xs;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = zs;
	tri_z[tricount][2] = zs;
	++tricount;

	// Tri 6
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xs;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ys;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = zs;
	++tricount;
	
	// Face 2
	// Tri 7
	tri_x[tricount][0] = xe;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ye;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = zs;
	tri_z[tricount][2] = zs;
	++tricount;

	// Tri 8
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ye;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = zs;
	++tricount;

	// Face 5
	// Tri 9
	tri_x[tricount][0] = xe;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ys;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = zs;
	tri_z[tricount][1] = zs;
	tri_z[tricount][2] = zs;
	++tricount;

	// Tri 10
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ye;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ys;

	tri_z[tricount][0] = zs;
	tri_z[tricount][1] = zs;
	tri_z[tricount][2] = zs;
	++tricount;

	// Face 6
	// Tri 11
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xe;

	tri_y[tricount][0] = ys;
	tri_y[tricount][1] = ys;
	tri_y[tricount][2] = ye;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = ze;
	++tricount;

	// Tri 12
	tri_x[tricount][0] = xs;
	tri_x[tricount][1] = xe;
	tri_x[tricount][2] = xs;

	tri_y[tricount][0] = ys;
	tri_y[tricount][1] = ye;
	tri_y[tricount][2] = ye;

	tri_z[tricount][0] = ze;
	tri_z[tricount][1] = ze;
	tri_z[tricount][2] = ze;
	++tricount;
}


void sixdof_sflow::geometry_refinement(lexer *p)
{
	double x0,x1,x2,y0,y1,y2,z0,z1,z2;
	double x01,x02,x12,y01,y02,y12,z01,z02,z12;
	double at,bt,ct,st;
	double nx_old,ny_old,nz_old;	
	
	tri_x_r.reserve(3*tricount);
	tri_y_r.reserve(3*tricount);
	tri_z_r.reserve(3*tricount);	
	
	tri_x_r.resize(tricount,vector<double>(3,0.0));
	tri_y_r.resize(tricount,vector<double>(3,0.0));
	tri_z_r.resize(tricount,vector<double>(3,0.0));
	
	
	for (int i = 0; i < tricount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tri_x_r[i][j] = tri_x[i][j];
			tri_y_r[i][j] = tri_y[i][j];
			tri_z_r[i][j] = tri_z[i][j];
		}
	}
	
	
	double critL = p->DXM*0.7;
	
	for (int n = 0; n < tri_x_r.size(); n++)
	{
		x0 = tri_x_r[n][0];
		x1 = tri_x_r[n][1];
		x2 = tri_x_r[n][2];
		
		y0 = tri_y_r[n][0];
		y1 = tri_y_r[n][1];
		y2 = tri_y_r[n][2];
		
		z0 = tri_z_r[n][0];
		z1 = tri_z_r[n][1];
		z2 = tri_z_r[n][2];  
           
		at = sqrt(pow(x1-x0,2.0) + pow(y1-y0,2.0) + pow(z1-z0,2.0));
		bt = sqrt(pow(x1-x2,2.0) + pow(y1-y2,2.0) + pow(z1-z2,2.0));
		ct = sqrt(pow(x2-x0,2.0) + pow(y2-y0,2.0) + pow(z2-z0,2.0));   
		   
		
		// Check size of triangle and split into 4 triangles if too big
		
		if ((at + bt + ct)/3.0 > critL)
		{
			// Half points
			
			x01 = x0 + (x1 - x0)/2.0;
			y01 = y0 + (y1 - y0)/2.0;
			z01 = z0 + (z1 - z0)/2.0;

			x02 = x0 + (x2 - x0)/2.0;
			y02 = y0 + (y2 - y0)/2.0;
			z02 = z0 + (z2 - z0)/2.0;			

			x12 = x1 + (x2 - x1)/2.0;
			y12 = y1 + (y2 - y1)/2.0;
			z12 = z1 + (z2 - z1)/2.0;
			
			
			// Old normal vector    
				
			nx_old = (y1 - y0) * (z2 - z0) - (y2 - y0) * (z1 - z0);
			ny_old = (x2 - x0) * (z1 - z0) - (x1 - x0) * (z2 - z0); 
			nz_old = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
			
			
			// Delete old and add new triangles
		
			tri_x_r.erase(tri_x_r.begin() + n); 
			tri_y_r.erase(tri_y_r.begin() + n); 
			tri_z_r.erase(tri_z_r.begin() + n); 
			n--;

			create_triangle(x0,y0,z0,x01,y01,z01,x02,y02,z02,nx_old,ny_old,nz_old);
			create_triangle(x01,y01,z01,x12,y12,z12,x02,y02,z02,nx_old,ny_old,nz_old);
			create_triangle(x01,y01,z01,x1,y1,z1,x12,y12,z12,nx_old,ny_old,nz_old);
			create_triangle(x02,y02,z02,x12,y12,z12,x2,y2,z2,nx_old,ny_old,nz_old);
		
            if (tri_x_r.size() > 1000) break;
		}
		
		if (tri_x_r.size() > 1000) break;
	}
	
	
	p->Dresize(tri_x,tricount,tri_x_r.size(),3,3);
	p->Dresize(tri_y,tricount,tri_y_r.size(),3,3);
	p->Dresize(tri_z,tricount,tri_z_r.size(),3,3);
	p->Dresize(tri_x0,tricount,tri_x_r.size(),3,3);
	p->Dresize(tri_y0,tricount,tri_y_r.size(),3,3);
	p->Dresize(tri_z0,tricount,tri_z_r.size(),3,3);
	
	tricount = tri_x_r.size();
	tend[0] = tricount;
	
	for (int i = 0; i < tricount; i++)
	{
		for (int j = 0; j < 3; j++)
		{	
			tri_x[i][j] = tri_x_r[i][j];
			tri_y[i][j] = tri_y_r[i][j];
			tri_z[i][j] = tri_z_r[i][j];
		}
	}
}


void sixdof_sflow::create_triangle
(
	double& x0, double& y0, double& z0,
	double& x1, double& y1, double& z1,
	double& x2, double& y2, double& z2,
	const double& nx_old, const double& ny_old, const double& nz_old
)
{
	double nx,ny,nz,temp;
	
	vector<double> tri_x_new(3,0.0);
	vector<double> tri_y_new(3,0.0);
	vector<double> tri_z_new(3,0.0);

	
	// Calculate new normal vector
	
	nx = (y1 - y0) * (z2 - z0) - (y2 - y0) * (z1 - z0);
	ny = (x2 - x0) * (z1 - z0) - (x1 - x0) * (z2 - z0); 
	nz = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);		

	nx = nx > 1.0e-5 ? nx : nx_old;
	ny = ny > 1.0e-5 ? ny : ny_old;
	nz = nz > 1.0e-5 ? nz : nz_old;	
	
	
	// Arrange triangle such that normal vector points outward
	
	if 
	(
		   SIGN(nx) != SIGN(nx_old) 
		|| SIGN(ny) != SIGN(ny_old) 
		|| SIGN(nz) != SIGN(nz_old)
	)
	{
		tri_x_new[0] = x2;
		tri_x_new[1] = x1;
		tri_x_new[2] = x0;

		tri_y_new[0] = y2;
		tri_y_new[1] = y1;
		tri_y_new[2] = y0;

		tri_z_new[0] = z2;
		tri_z_new[1] = z1;
		tri_z_new[2] = z0;				
	}
	else
	{	
		tri_x_new[0] = x0;
		tri_x_new[1] = x1;
		tri_x_new[2] = x2;

		tri_y_new[0] = y0;
		tri_y_new[1] = y1;
		tri_y_new[2] = y2;

		tri_z_new[0] = z0;
		tri_z_new[1] = z1;
		tri_z_new[2] = z2;	
	}
	
	
	// Add triangle to list
	
	tri_x_r.push_back(tri_x_new);
	tri_y_r.push_back(tri_y_new);
	tri_z_r.push_back(tri_z_new);
}
