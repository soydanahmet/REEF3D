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

#include"boundarycheck.h"
#include"bedshear.h"
#include<iostream>
#include<fstream>

class lexer;
class fdm;
class ghostcell;
class field;
class sediment;

using namespace std;

#ifndef BEDSHEAR_MAX_H_
#define BEDSHEAR_MAX_H_

class bedshear_max : public boundarycheck
{
public:
    bedshear_max(lexer*,fdm*,ghostcell*);
	virtual ~bedshear_max();

	void bedshear_maxval(lexer*, fdm*, ghostcell*, sediment*);


private:
    int n;
    ofstream bsgout;

};

#endif
