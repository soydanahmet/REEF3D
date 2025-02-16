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

#include"komega_IM1.h"
#include"lexer.h"
#include"fdm.h"
#include"ghostcell.h"
#include"strain.h"
#include"solver.h"
#include"diffusion.h"
#include"ioflow.h"
#include"convection.h"

komega_IM1::komega_IM1(lexer* p, fdm* a, ghostcell *pgc) : ikomega(p,a,pgc),kn(p),en(p)
{
	gcval_kin=20;
	gcval_eps=30;
}

komega_IM1::~komega_IM1()
{
}

void komega_IM1::start(fdm* a, lexer* p, convection* pconvec, diffusion* pdiff,solver* psolv, ghostcell* pgc, ioflow* pflow, vrans *pvrans)
{
	Pk_update(p,a,pgc);
	wallf_update(p,a,pgc,wallf);

//kin
    starttime=pgc->timer();
	clearrhs(p,a);
    pconvec->start(p,a,kin,4,a->u,a->v,a->w);
	pdiff->idiff_scalar(p,a,pgc,psolv,kin,a->visc,kw_sigma_k,1.0);
	kinsource(p,a,pvrans);
	timesource(p,a,kn);
    bckeps_start(a,p,kin,eps,gcval_kin);
	psolv->start(p,a,pgc,kin,a->rhsvec,4);
	pgc->start4(p,kin,gcval_kin);
	p->kintime=pgc->timer()-starttime;
	p->kiniter=p->solveriter;
	if(p->mpirank==0 && (p->count%p->P12==0))
	cout<<"kin_iter: "<<p->kiniter<<"  kin_time: "<<setprecision(3)<<p->kintime<<endl;

//omega
    starttime=pgc->timer();
	clearrhs(p,a);
    pconvec->start(p,a,eps,4,a->u,a->v,a->w);
	pdiff->idiff_scalar(p,a,pgc,psolv,eps,a->visc,kw_sigma_w,1.0);
	epssource(p,a,pvrans);
	timesource(p,a,en);
	psolv->start(p,a,pgc,eps,a->rhsvec,4);
	epsfsf(p,a,pgc);
	bckeps_start(a,p,kin,eps,gcval_eps);
	pgc->start4(p,eps,gcval_eps);
	p->epstime=pgc->timer()-starttime;
	p->epsiter=p->solveriter;
	if(p->mpirank==0 && (p->count%p->P12==0))
	cout<<"omega_iter: "<<p->epsiter<<"  omega_time: "<<setprecision(3)<<p->epstime<<endl;

	eddyvisc(p,a,pgc,pvrans);
    pflow->turb_relax(p,a,pgc,a->eddyv);
	pgc->start4(p,a->eddyv,24);
}

void komega_IM1::ktimesave(lexer *p, fdm* a, ghostcell *pgc)
{
    LOOP
    kn(i,j,k)=kin(i,j,k); 
}

void komega_IM1::etimesave(lexer *p, fdm* a, ghostcell *pgc)
{
    LOOP
    en(i,j,k)=eps(i,j,k); 
}

void komega_IM1::timesource(lexer* p, fdm* a, field& fn)
{
    count=0;
    LOOP
    {
        a->M.p[count] += 1.0/DT;

        a->rhsvec.V[count] += a->L(i,j,k) + fn(i,j,k)/DT;

	++count;
    }
}

void komega_IM1::clearrhs(lexer* p, fdm* a)
{
    count=0;
    LOOP
    {
    a->rhsvec.V[count]=0.0;
	a->L(i,j,k)=0.0;
	++count;
    }
}
