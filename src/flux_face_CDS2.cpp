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

#include"flux_face_CDS2.h"
#include"lexer.h"
#include"fdm.h"

flux_face_CDS2::flux_face_CDS2(lexer *pp)
{
p=pp;
}

flux_face_CDS2::~flux_face_CDS2()
{
}

void flux_face_CDS2::u_flux(fdm* a,int ipol, field& uvel, double &uflux1, double &uflux2)
{
	if(ipol==1)
	{
    pip=1;
	uflux1= 0.5*(uvel(i,j,k)+uvel(i-1,j,k));
	uflux2= 0.5*(uvel(i,j,k)+uvel(i+1,j,k));
	pip=0;
	}

	if(ipol==2)
	{
	pip=1;
	uflux1= 0.5*(uvel(i-1,j,k)+uvel(i-1,j+1,k));
	uflux2= 0.5*(uvel(i,j,k)+uvel(i,j+1,k));
	pip=0;
	}

	if(ipol==3)
	{
	pip=1;
	uflux1= 0.5*(uvel(i-1,j,k)+uvel(i-1,j,k+1));
	uflux2= 0.5*(uvel(i,j,k)+uvel(i,j,k+1));
	pip=0;
	}

	if(ipol==4)
	{
    pip=1;
	uflux1= uvel(i-1,j,k);
	uflux2= uvel(i,j,k);
    pip=0;
	}
}

void flux_face_CDS2::v_flux(fdm* a, int ipol, field& vvel, double &vflux1, double &vflux2)
{
	if(ipol==1)
	{
	pip=2;
	vflux1= 0.5*(vvel(i,j-1,k)+vvel(i+1,j-1,k));
	vflux2= 0.5*(vvel(i,j,k)+vvel(i+1,j,k));
	pip=0;
	}

	if(ipol==2)
	{
    pip=2;
	vflux1= 0.5*(vvel(i,j,k)+vvel(i,j-1,k));
	vflux2= 0.5*(vvel(i,j,k)+vvel(i,j+1,k));
	pip=0;
	}

	if(ipol==3)
	{
	pip=2;
	vflux1= 0.5*(vvel(i,j-1,k)+vvel(i,j-1,k+1));
	vflux2= 0.5*(vvel(i,j,k)+vvel(i,j,k+1));
	pip=0;
	}

	if(ipol==4)
	{
    pip=2;
	vflux1= vvel(i,j-1,k);
	vflux2= vvel(i,j,k);
    pip=0;
	}
}

void flux_face_CDS2::w_flux(fdm* a, int ipol, field& wvel, double &wflux1, double &wflux2)
{

	if(ipol==1)
	{
	pip=3;
	wflux1= 0.5*(wvel(i,j,k-1)+wvel(i+1,j,k-1));
	wflux2= 0.5*(wvel(i,j,k)+wvel(i+1,j,k));
	pip=0;
	}

	if(ipol==2)
	{
	pip=3;
	wflux1= 0.5*(wvel(i,j,k-1)+wvel(i,j+1,k-1));
	wflux2= 0.5*(wvel(i,j,k)+wvel(i,j+1,k));
	pip=0;
	}

	if(ipol==3)
	{
    pip=3;
	wflux1= 0.5*(wvel(i,j,k)+wvel(i,j,k-1));
	wflux2= 0.5*(wvel(i,j,k)+wvel(i,j,k+1));
	pip=0;
	}

	if(ipol==4)
	{
    pip=3;
	wflux1= wvel(i,j,k-1);
	wflux2= wvel(i,j,k);
    pip=0;
	}
}

void flux_face_CDS2::omega_flux(lexer *p, fdm* a, int ipol, field &u, field &v, field &w, double &wflux1, double &wflux2)
{

	if(ipol==1)
	{
	pip=3;
	wflux1  = 0.5*(a->w(i,j,k-1)+a->w(i+1,j,k-1))*0.5*(p->sigz[IJ]+p->sigz[Ip1J]) 
            + 0.5*(p->sigt[FIJK]+p->sigt[FIp1JK])
            + 0.5*(a->u(i,j,k) + a->u(i,j,k-1))*p->sigx[FIJK]
            + 0.25*(a->v(i,j,k) + a->v(i,j,k-1) + a->v(i,j+1,k) + a->v(i,j+1,k-1))*p->sigy[FIJK];
            
	wflux2  = 0.5*(a->w(i,j,k)+a->w(i+1,j,k))*0.5*(p->sigz[IJ]+p->sigz[Ip1J])     
            + 0.5*(p->sigt[FIJKp1]+p->sigt[FIp1JKp1])
            + 0.5*(a->u(i,j,k) + a->u(i,j,k+1))*p->sigx[FIJKp1]
            + 0.25*(a->v(i,j,k) + a->v(i,j,k+1) + a->v(i,j+1,k) + a->v(i,j+1,k+1))*p->sigy[FIJKp1];
	pip=0;
	}

	if(ipol==2)
	{
	pip=3;
	wflux1  = 0.5*(a->w(i,j,k-1)+a->w(i,j+1,k-1))*0.5*(p->sigz[IJ]+p->sigz[IJp1]) 
            + 0.5*(p->sigt[FIJK]+p->sigt[FIJp1K])
            + 0.25*(a->u(i-1,j,k) + a->u(i-1,j,k-1) + a->u(i,j,k) + a->u(i,j,k-1))*p->sigx[FIJK]
            + 0.25*(a->v(i,j-1,k) + a->v(i,j-1,k-1) + a->v(i,j,k) + a->v(i,j,k-1))*p->sigy[FIJK];
            
	wflux2  = 0.5*(a->w(i,j,k)+a->w(i,j+1,k))*0.5*(p->sigz[IJ]+p->sigz[IJp1])     
            + 0.5*(p->sigt[FIJKp1]+p->sigt[FIJp1Kp1])
            + 0.25*(a->u(i-1,j,k) + a->u(i-1,j,k+1) + a->u(i,j,k) + a->u(i,j,k+1))*p->sigx[FIJKp1]
            + 0.25*(a->v(i,j-1,k) + a->v(i,j-1,k+1) + a->v(i,j,k) + a->v(i,j,k+1))*p->sigy[FIJKp1];
	pip=0;
	}

	if(ipol==3)
	{
    pip=3;
	wflux1  = 0.5*(a->w(i,j,k)+a->w(i,j,k-1))*p->sigz[IJ] 
            + 0.5*(p->sigt[FIJKp1]+p->sigt[FIJK]) 
            + 0.5*(a->u(i-1,j,k) + a->u(i,j,k))*p->sigx[FIJK]
            + 0.5*(a->v(i,j-1,k) + a->v(i,j,k))*p->sigy[FIJK];
         
	wflux2  = 0.5*(a->w(i,j,k)+a->w(i,j,k+1))*p->sigz[IJ] 
            + 0.5*(p->sigt[FIJKp1]+p->sigt[FIJKp2]);
            + 0.5*(a->u(i-1,j,k+1) + a->u(i,j,k+1))*p->sigx[FIJKp1]
            + 0.5*(a->v(i,j-1,k+1) + a->v(i,j,k+1))*p->sigy[FIJKp1];
	pip=0;
	}

	if(ipol==4)
	{
    pip=3;
	wflux1= a->w(i,j,k-1)*p->sigz[IJ] + p->sigt[FIJK];
	wflux2= a->w(i,j,k)*p->sigz[IJ]   + p->sigt[FIJKp1];
    pip=0;
	}
}

