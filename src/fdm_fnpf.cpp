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

#include"fdm_fnpf.h"
#include"lexer.h"

fdm_fnpf::fdm_fnpf(lexer *p) : press(p),test(p),Fifsf(p),Fibed(p),
                              nodeval(p),eta(p),etaloc(p),
                              wet(p),wet_n(p),breaking(p),breaklog(p),bc(p),
                              eta_n(p),WL(p),bed(p),depth(p),Fz(p),K(p),
                              Fx(p),Fy(p),
                              Ex(p),Ey(p),Exx(p),Eyy(p),
                              Bx(p),By(p),Bxx(p),Byy(p),
                              Hx(p),Hy(p),
                              coastline(p),vb(p),
                              nodeval2D(p),breaking_print(p),
                              rhsvec(p),rvec(p),xvec(p),N(p),M(p)
{    
    p->Darray(U,p->imax*p->jmax*(p->kmax+2));
    p->Darray(V,p->imax*p->jmax*(p->kmax+2));
    p->Darray(W,p->imax*p->jmax*(p->kmax+2));
    p->Darray(Fi,p->imax*p->jmax*(p->kmax+2));
    p->Darray(Uin,p->imax*p->jmax*(p->kmax+2));

    C4.allocate(p);
}













