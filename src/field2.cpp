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

#include"field2.h"
#include"lexer.h"
#include"fdm.h"
#include"cart2.h"

field2::field2(lexer *p)
{
    imin=p->imin;
    imax=p->imax;
    jmin=p->jmin;
    jmax=p->jmax;
    kmin=p->kmin;
    kmax=p->kmax;

	fieldalloc(p);
	fieldgcalloc(p);
	
	pp=p;
}

field2::~field2()
{
    int a,b;
    
    for(a=0;a<gcfeldsize;++a)
    for(b=0;b<6;++b)
	delete [ ] gcfeld[a][b];
    
	for(a=0;a<gcfeldsize;++a)
	delete [ ] gcfeld[a];

	delete [ ] gcfeld;

	delete [ ] V;
}

void field2::fieldalloc(lexer* p)
{
	int gridsize = p->imax*p->jmax*p->kmax;
	p->Darray(V,gridsize);
}

void field2::dealloc(lexer* p)
{
    int a,b;
    
    for(a=0;a<gcfeldsize;++a)
    for(b=0;b<6;++b)
	delete [ ] gcfeld[a][b];
    
	for(a=0;a<gcfeldsize;++a)
	delete [ ] gcfeld[a];

	delete [ ] gcfeld;

	delete [ ] V;
    
    gcfeldsize=feldsize=0;
}

void field2::resize(lexer* p)
{
    int factor=3;
    
    p->Dresize(gcfeld,gcfeldsize, p->gcextra2*factor, 6, 6, 4, 4); 

	gcfeldsize=p->gcextra2*factor;
}

void field2::fieldgcalloc(lexer*& p)
{
    gcfeldsize=p->gcbextra;
	
	p->Darray(gcfeld,gcfeldsize,6,4);
}

double & field2::operator[](int n)
{
	return V[n];
}

//------------------------------------------------------------------------------

double & field2::operator()(int ii, int jj, int kk)
{	
	if(pp->mgc2[(ii-imin)*jmax*kmax + (jj-jmin)*kmax + kk-kmin]<2)
	return V[(ii-imin)*jmax*kmax + (jj-jmin)*kmax + kk-kmin];
	
	
	iter=(ii-imin)*jmax*kmax + (jj-jmin)*kmax + kk-kmin;
	
		di=ii-i;
		dj=jj-j;
		dk=kk-k;
	

		if(pip==4)
		return V[iter];
        
        if(di==0 && dj==0 && dk==0 && pp->flag2[iter]>0)
		return V[iter];
        
        if(((di!=0 && dj!=0) || (di!=0 && dk!=0) || (dj!=0 && dk!=0)) && pip==0)
		return V[iter];
        
        if(di==0 && dj==0 && dk==0 && pip==5)
		{
			dj=1;
            if(pp->gcorig2[pp->mgc2[iter]-10][1][dj]==0)
            return V[iter];
			
			if(pp->gcorig2[pp->mgc2[iter]-10][1][dj]==1)
			return gcfeld[pp->mgc2[iter]-10][1][dj];
		}
        
        if(di==0 && dj<0 && dk==0 && pip==5)
		{
			 dj=-1;
            if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj]==0)
            return V[iter];
			
			if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj]==1)
			return gcfeld[pp->mgc2[iter]-10][2][-dj];
		}
        
        
        
		
		if(di==0 && dj==0 && dk==0 && pip!=2)
		return V[iter];
        
        /*
        if(di==0 && dj==0 && dk==0 && pip==2)
		dj=1;
        
        if(dj==0 && pip==2)
		dj=1;*/

	  
//1
		if(di<0 && ((dj==0 && dk==0) || pip==1))
		{
			if(pp->gcorig2[pp->mgc2[iter]-10][0][-di]==0)
            {
            if(di<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][0][-di-1]==1)
			return gcfeld[pp->mgc2[iter]-10][0][-di-1];
            
            if(di<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][0][-di-2]==1)
			return gcfeld[pp->mgc2[iter]-10][0][-di-2];
            
            if(di<-1)
            if(pp->gcorig2[pp->mgc2[iter]-10][0][-di-1]==1)
			return gcfeld[pp->mgc2[iter]-10][0][-di-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][0][-di]==1)
			return gcfeld[pp->mgc2[iter]-10][0][-di];
		}
//4
		if(di>0 && ((dj==0 && dk==0) || pip==1))
		{
            if(pp->gcorig2[pp->mgc2[iter]-10][3][di]==0)
            {
            if(di>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][3][di-1]==1)
			return gcfeld[pp->mgc2[iter]-10][3][di-1];
            
            if(di>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][3][di-2]==1)
			return gcfeld[pp->mgc2[iter]-10][3][di-2];
            
            if(di>1)
            if(pp->gcorig2[pp->mgc2[iter]-10][3][di-1]==1)
			return gcfeld[pp->mgc2[iter]-10][3][di-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][3][di]==1)
			return gcfeld[pp->mgc2[iter]-10][3][di];
		}

//3
		if(dj<0 && ((di==0 && dk==0) || pip==2))
		{
            if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj]==0)
            {
            if(dj<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj-1]==1)
			return gcfeld[pp->mgc2[iter]-10][2][-dj-1];
            
            if(dj<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj-2]==1)
			return gcfeld[pp->mgc2[iter]-10][2][-dj-2];
            
            if(dj<-1)
            if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj-1]==1)
			return gcfeld[pp->mgc2[iter]-10][2][-dj-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][2][-dj]==1)
			return gcfeld[pp->mgc2[iter]-10][2][-dj];
		}
//2
		if(dj>0 && ((di==0 && dk==0) || pip==2))
		{
            if(pp->gcorig2[pp->mgc2[iter]-10][1][dj]==0)
            {
            if(dj>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][1][dj-1]==1)
			return gcfeld[pp->mgc2[iter]-10][1][dj-1];
            
            if(dj>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][1][dj-2]==1)
			return gcfeld[pp->mgc2[iter]-10][1][dj-2];
            
            if(dj>1)
            if(pp->gcorig2[pp->mgc2[iter]-10][1][dj-1]==1)
			return gcfeld[pp->mgc2[iter]-10][1][dj-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][1][dj]==1)
			return gcfeld[pp->mgc2[iter]-10][1][dj];
		}

//5
		if(dk<0 && ((di==0 && dj==0) || pip==3))
		{
            if(pp->gcorig2[pp->mgc2[iter]-10][4][-dk]==0)
            {
            if(dk<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][4][-dk-1]==1)
			return gcfeld[pp->mgc2[iter]-10][4][-dk-1];
            
            if(dk<-2)
            if(pp->gcorig2[pp->mgc2[iter]-10][4][-dk-2]==1)
			return gcfeld[pp->mgc2[iter]-10][4][-dk-2];
            
            if(dk<-1)
            if(pp->gcorig2[pp->mgc2[iter]-10][4][-dk-1]==1)
			return gcfeld[pp->mgc2[iter]-10][4][-dk-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][4][-dk]==1)
			return gcfeld[pp->mgc2[iter]-10][4][-dk];
		}

//6
		if(dk>0 && ((di==0 && dj==0) || pip==3))
		{
            if(pp->gcorig2[pp->mgc2[iter]-10][5][dk]==0)
            {
            if(dk>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][5][dk-1]==1)
			return gcfeld[pp->mgc2[iter]-10][5][dk-1];
            
            if(dk>2)
            if(pp->gcorig2[pp->mgc2[iter]-10][5][dk-2]==1)
			return gcfeld[pp->mgc2[iter]-10][5][dk-2];
            
            if(dk>1)
            if(pp->gcorig2[pp->mgc2[iter]-10][5][dk-1]==1)
			return gcfeld[pp->mgc2[iter]-10][5][dk-1];
            
            return V[iter];
            }
			
			if(pp->gcorig2[pp->mgc2[iter]-10][5][dk]==1)
			return gcfeld[pp->mgc2[iter]-10][5][dk];
		}
	

	return V[iter];
}
