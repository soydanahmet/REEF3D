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
Author: Hans Bihs
--------------------------------------------------------------------*/

#include"sandslide_f3.h"
#include"sediment_fdm.h"
#include"lexer.h"
#include"fdm.h"
#include"ghostcell.h"
#include"sliceint.h"

sandslide_f3::sandslide_f3(lexer *p) : norm_vec(p), bedslope(p), fh(p)
{
    if(p->S50==1)
	gcval_topo=151;

	if(p->S50==2)
	gcval_topo=152;

	if(p->S50==3)
	gcval_topo=153;
	
	if(p->S50==4)
	gcval_topo=154;

	fac1 = (1.0/6.0);
	fac2 = (1.0/12.0);
}

sandslide_f3::~sandslide_f3()
{
}

void sandslide_f3::start(lexer *p, fdm * a, ghostcell *pgc, sediment_fdm *s)
{
    SLICELOOP4
    s->slideflag(i,j)=0.0;
    
    if(p->mpirank==0)
    cout<<"sandslide_f3"<<endl;
    
    // mainloop
    for(int qn=0; qn<p->S91; ++qn)
    {
        count=0;
        
        // fill
        SLICELOOP4
        fh(i,j)=0.0;
        
        pgc->gcsl_start4(p,fh,1);
        
        // slide loop
        SLICELOOP4
        if(p->pos_x()>p->S77_xs && p->pos_x()<p->S77_xe)
        {
            slide(p,a,pgc,s);
        }
        
        pgc->gcslparax_fh(p,fh,4);
        
        // fill back
        SLICELOOP4
        a->bedzh(i,j)+=fh(i,j);
        

        pgc->gcsl_start4(p,a->bedzh,1);

        count=pgc->globalimax(count);

        p->slidecells=count;
        
        if(p->slidecells==0)
        break;

        if(p->mpirank==0)
        cout<<"sandslide_f3 corrections: "<<p->slidecells<<endl;
    }
}

void sandslide_f3::slide(lexer *p, fdm * a, ghostcell *pgc, sediment_fdm *s)
{   
        
        double dzp=0.0;
        int Iup=0;
        int id[8];
		k = a->bedk(i,j);
        
        
        for(int qn=0; qn<8; ++qn)
        id[qn]=0;
        
			
        // 1
        dh = a->bedzh(i-1,j) - a->bedzh(i,j);
        
        maxdh = tan(s->phi(i,j))*p->DXP[IM1];
        
        if(dh>maxdh && fabs(dh)<1.0e15)
		{
            
            dh_corr = (dh-maxdh) + tan(p->S93*(PI/180.0))*p->DXP[IM1];

            dzp += dh_corr;
            ++Iup;
            
            id[0]=1;
            
            s->slideflag(i,j)=1.0;
            
		++count;
		}

        // 2
        dh = a->bedzh(i+1,j) - a->bedzh(i,j);
        
        maxdh = tan(s->phi(i,j))*p->DXP[IP];
		
        if(dh>maxdh && fabs(dh)<1.0e15)
		{
			dh_corr = (dh-maxdh) + tan(p->S93*(PI/180.0))*p->DXP[IP];

            dzp += dh_corr;
            ++Iup;
            
            id[1]=1;
            
            s->slideflag(i,j)=1.0;
			
        ++count;
        }

        // 3
        dh = a->bedzh(i,j-1) - a->bedzh(i,j);
        
        maxdh = tan(s->phi(i,j))*p->DYP[JM1];
        
        if(dh>maxdh && fabs(dh)<1.0e15)
		{          
            dh_corr = (dh-maxdh) + tan(p->S93*(PI/180.0))*p->DYP[JM1];

            dzp += dh_corr;
            ++Iup;
            
            id[2]=1;
            
            s->slideflag(i,j)=1.0;
			
        ++count;
        }

        // 4
        dh = a->bedzh(i,j+1) - a->bedzh(i,j);
		dh_corr = dh + tan(p->S93*(PI/180.0))*p->DYP[JP];
        
        maxdh = tan(s->phi(i,j))*p->DYP[JP];
        
        if(dh>maxdh && fabs(dh)<1.0e15)
		{
            dh_corr = (dh-maxdh) + tan(p->S93*(PI/180.0))*p->DYP[JP];

            dzp += dh_corr;
            ++Iup;
            
            id[3]=1;
            
            s->slideflag(i,j)=1.0;

        ++count;
        }
		
		
        // 5
        dh = a->bedzh(i-1,j-1) - a->bedzh(i,j);
        
        maxdhs = tan(s->phi(i,j))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JM1]*p->DYP[JM1]);

        if(dh>maxdhs && fabs(dh)<1.0e15)
        {
            dh_corr = (dh-maxdhs) + tan(p->S93*(PI/180.0))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JM1]*p->DYP[JM1]);

            dzp += dh_corr;
            ++Iup;
            
            id[4]=1;
            
            s->slideflag(i,j)=1.0;
        
        ++count;
        }
    

        // 6
        dh = a->bedzh(i-1,j+1) - a->bedzh(i,j);

        maxdhs = tan(s->phi(i,j))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JP]*p->DYP[JP]);
        
        if(dh>maxdhs && fabs(dh)<1.0e15)
		{   
             dh_corr = (dh-maxdhs) + tan(p->S93*(PI/180.0))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JP]*p->DYP[JP]);  

            dzp += dh_corr;
            ++Iup;
            
            id[5]=1;
            
            s->slideflag(i,j)=1.0;
			
        ++count;
        }

        // 7
        dh = a->bedzh(i+1,j-1) - a->bedzh(i,j);
 
        maxdhs = tan(s->phi(i,j))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JM1]*p->DYP[JM1]);
        
        if(dh>maxdhs && fabs(dh)<1.0e15)
		{
            dh_corr = (dh-maxdhs) + tan(p->S93*(PI/180.0))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JM1]*p->DYP[JM1]);

            dzp += dh_corr;
            ++Iup;
            
            id[6]=1;
            
            s->slideflag(i,j)=1.0;

        ++count;
        }
    
    
        // 8
        dh =  a->bedzh(i+1,j+1) - a->bedzh(i,j);
  
        maxdhs = tan(s->phi(i,j))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JP]*p->DYP[JP]);

        if(dh>maxdhs && fabs(dh)<1.0e15)
		{   
            dh_corr = (dh-maxdhs) + tan(p->S93*(PI/180.0))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JP]*p->DYP[JP]);   

            dzp += dh_corr;
            ++Iup;
            
            id[7]=1;
            
            s->slideflag(i,j)=1.0;
            
        ++count;
        }
        
        dzp = dzp/double(Iup + 1);
        
        fh(i,j) +=dzp;
        
        if(id[0]==1)
        fh(i-1,j) += dzp + a->bedzh(i,j) - a->bedzh(i-1,j) + tan(s->phi(i,j))*p->DXP[IM1] - tan(p->S93*(PI/180.0))*p->DXP[IM1]; 
        
        if(id[1]==1)
        fh(i+1,j) += dzp + a->bedzh(i,j) - a->bedzh(i+1,j) + tan(s->phi(i,j))*p->DXP[IP] - tan(p->S93*(PI/180.0))*p->DXP[IP];
        
        if(id[2]==1)
        fh(i,j-1) += dzp + a->bedzh(i,j) - a->bedzh(i,j-1) + tan(s->phi(i,j))*p->DYP[JM1] - tan(p->S93*(PI/180.0))*p->DYP[JM1];
        
        if(id[3]==1)
        fh(i,j+1) += dzp + a->bedzh(i,j) - a->bedzh(i,j+1) + tan(s->phi(i,j))*p->DYP[JP] - tan(p->S93*(PI/180.0))*p->DYP[JP];
        
        if(id[4]==1)
        fh(i-1,j-1) += dzp + a->bedzh(i,j) - a->bedzh(i-1,j-1) + tan(s->phi(i,j))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JM1]*p->DYP[JM1]) - tan(p->S93*(PI/180.0))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JM1]*p->DYP[JM1]);
        
        if(id[5]==1)
        fh(i-1,j+1) += dzp + a->bedzh(i,j) - a->bedzh(i-1,j+1) + tan(s->phi(i,j))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JP]*p->DYP[JP]) - tan(p->S93*(PI/180.0))*sqrt(p->DXP[IM1]*p->DXP[IM1] + p->DYP[JP]*p->DYP[JP]);  
        
        if(id[6]==1)
        fh(i+1,j-1) += dzp + a->bedzh(i,j) - a->bedzh(i+1,j-1) + tan(s->phi(i,j))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JM1]*p->DYP[JM1]) - tan(p->S93*(PI/180.0))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JM1]*p->DYP[JM1]);
        
        if(id[7]==1)
        fh(i+1,j+1) += dzp + a->bedzh(i,j) - a->bedzh(i+1,j+1) + tan(s->phi(i,j))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JP]*p->DYP[JP]) -tan(p->S93*(PI/180.0))*sqrt(p->DXP[IP]*p->DXP[IP] + p->DYP[JP]*p->DYP[JP]);
        
        
        
    // dzi
}

void sandslide_f3::topo_zh_update(lexer *p, fdm *a,ghostcell *pgc)
{
	pgc->gcsl_start4(p,a->bedzh,1);
	
    ALOOP
    {
    if(p->pos_x()>p->S77_xs && p->pos_x()<p->S77_xe)
    a->topo(i,j,k)=-a->bedzh(i,j)+p->pos_z();
    }
	
	pgc->start4a(p,a->topo,150);
}

