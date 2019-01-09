/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2019 Hans Bihs

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

#include"flowfile_in.h"
#include"lexer.h"
#include"fdm.h"
#include"ghostcell.h"
#include"turbulence.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

flowfile_in::flowfile_in(lexer *p, ghostcell *pgc) 
{	
    if(p->I230>0 && p->gcin_count>0)
    {
    header_read(p,pgc);
    
    dk = conv((p->I231)/p->dx);

    maxk = Nk-dk;
    
    startup=0;
    }
}

flowfile_in::~flowfile_in()
{
}

void flowfile_in::flowfile_start(lexer *p, fdm *a, ghostcell *pgc, turbulence *pturb)
{
    if(p->gcin_count>0)
    {
        q0n=q0;
        q1n=q1;
        
        if(startup==0)
        {
        read0(p,a,pgc,pturb);
        read1(p,a,pgc,pturb);
        startup=1;
        }
        
        // find q0
        while(simtime[q0+1]<=p->simtime+p->I232)
        ++q0;
        
        // find q1
        while(simtime[q1]<p->simtime+p->I232)
        ++q1;
        
        q0=MIN(q0,entrycount);
        q1=MIN(q1,entrycount);

        
        if(q0!=q0n)
        {
        //close f0
        flowfile0.close();
        
        // Open File 0
        filename(p,a,pgc,name0,q0);
        flowfile0.open(name0, ios::binary);
        read0(p,a,pgc,pturb);
        }
        
        
        if(q1!=q1n)
        {
        //close f1
        flowfile1.close();
        
        // Open File 1
        filename(p,a,pgc,name1,q1);
        flowfile1.open(name1, ios::binary);
        read1(p,a,pgc,pturb);
        }
        
        // read ff0
        // read ff1
        /*
        cout<<p->mpirank<<" X0: "<<X0[0][5]<<" X1: "<<X1[0][5]<<p->mpirank<<" Z0: "<<Z0[0][9]<<" Z1: "<<Z1[0][9]<<endl;
        cout<<p->mpirank<<" U0: "<<U0[0][5]<<" U1: "<<U1[0][5]<<p->mpirank<<" LS0: "<<LS0[0][9]<<" LS1: "<<LS1[0][9]<<endl;
        cout<<p->mpirank<<" W0: "<<W0[0][5]<<" W1: "<<W1[0][5]<<p->mpirank<<" P0: "<<P0[0][9]<<" P1: "<<P1[0][9]<<endl;*/
        
        deltaT = simtime[q1]-simtime[q0];

        t0 = (simtime[q1]-(p->simtime+p->I232))/deltaT;
        t1 = ((p->simtime+p->I232)-simtime[q0])/deltaT;
    
    }
    
    /*cout<<"t0: "<<simtime[q0]<<" t1: "<<simtime[q1]<<endl;
    cout<<"t0: "<<t0<<" t1: "<<t1<<endl;*/
    
}


void flowfile_in::ff_inflow(lexer *p, fdm* a, ghostcell* pgc, field& u, field& v, field& w)
{
    double uval,vval,wval,pval;
    
    for(n=0;n<p->gcin_count;n++)
    {
    i=p->gcin[n][0];
    j=p->gcin[n][1];
    k=p->gcin[n][2];
    
    // U
    if(k<maxk && a->phi(i-1,j,k)>=0.6*p->dx)
    uval = U0[0][k+dk]*t0 + U1[0][k+dk]*t1;
    
    if(k>=maxk || a->phi(i-1,j,k)<-0.6*p->dx)
    uval = 0.0;

    u(i-1,j,k)=uval;
    u(i-2,j,k)=uval;
    u(i-3,j,k)=uval;
    
    // V 
    if(k<maxk && a->phi(i-1,j,k)>=0.6*p->dx)
    vval = V0[0][k+dk]*t0 + V1[0][k+dk]*t1;
    
    if(k>=maxk || a->phi(i-1,j,k)<-0.6*p->dx)
    vval = 0.0;
    
    v(i-1,j,k)=vval;
    v(i-2,j,k)=vval;
    v(i-3,j,k)=vval;
    

    // W
    if(k<maxk && a->phi(i-1,j,k)>=0.6*p->dx)
    wval = W0[0][k+dk]*t0 + W1[0][k+dk]*t1;
    
    if(k>=maxk || a->phi(i-1,j,k)<-0.6*p->dx)
    wval = 0.0;
	
    w(i-1,j,k)=wval;
    w(i-2,j,k)=wval;
    w(i-3,j,k)=wval;

    // P
    if(k<maxk && a->phi(i-1,j,k)>=0.6*p->dx)
    {
    pval = P0[0][k+dk]*t0 + P1[0][k+dk]*t1;
    
    a->press(i-1,j,k)=pval;
    a->press(i-2,j,k)=pval;
    a->press(i-3,j,k)=pval;
    }
    
    }
}

void flowfile_in::ff_waterlevel(lexer *p, fdm* a, ghostcell* pgc, field& ls)
{
    double lsval;
    double xp,yp,zp;
   
    for(n=0;n<p->gcin_count;n++)
    {
    i=p->gcin[n][0];
    j=p->gcin[n][1];
    k=p->gcin[n][2];
    
    if(k<maxk)
    {
    lsval = LS0[0][k+dk]*t0 + LS1[0][k+dk]*t1;


    ls(i-1,j,k)=lsval;
    ls(i-2,j,k)=lsval;
    ls(i-3,j,k)=lsval;
    }
    }
    
}

int flowfile_in::conv(double a)
{

int b,c;
double d,diff;

c= int( a);
d=double(c);
diff=a-d;

b=c;

if(diff>0.5)
b=c+1;

if(diff<=-0.5)
b=c-1;

return b;

}

