/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2019 Hans Bihs

This file is part of REEF3D.

REEF3D is fra->eps software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Fra->eps Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. Sa->eps the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, sa->eps <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
--------------------------------------------------------------------*/

class lexer;
class ghostcell;
class fdm_fnpf;
class fnpf_sg_laplace;
class slice;
class fnpf_convection;
class fnpf_ddx;
class fnpf_etadisc;

using namespace std;

#ifndef FNPF_SG_FSF_H_
#define FNPF_SG_FSF_H_

class fnpf_sg_fsf 
{
public:
   
    virtual void fsfdisc(lexer*,fdm_fnpf*,ghostcell*,slice&,slice&)=0;
    virtual void fsfdisc_ini(lexer*,fdm_fnpf*,ghostcell*,slice&,slice&)=0;
    virtual void kfsfbc(lexer*,fdm_fnpf*,ghostcell*)=0;
    virtual void dfsfbc(lexer*,fdm_fnpf*,ghostcell*,slice&)=0;
    virtual void fsfwvel(lexer*,fdm_fnpf*,ghostcell*,slice&,slice&)=0;
    virtual void wetdry(lexer*,fdm_fnpf*,ghostcell*,slice&,slice&)=0;
    virtual void breaking(lexer*,fdm_fnpf*,ghostcell*,slice&,slice&,slice&,double)=0;
    virtual void coastline(lexer*,fdm_fnpf*,ghostcell*,slice&)=0;
    
};

#endif