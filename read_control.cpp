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

#include"lexer.h"
#include <fstream>

void lexer::read_control()
{
	char c;
	int numint;
    int count=0;

	ifstream control("ctrl.txt", ios_base::in);
	if(!control)
	{
		cout<<endl<<("no 'ctrl.txt' file found")<<endl<<endl;
		exit(0);
	}
	
	if(mpirank==0)
	cout<<"read ctrl"<<endl;


	while(!control.eof())
	{
		control>>c;

	if (c == '/') 
	{
	control.ignore(1000, '\n');
	}
	else
	{	
		switch(c)
		{
        case 'A': control>>numint;
				switch(numint)
				{
				case 10: control>>A10;
						 clear(c,numint);
						 break;
				case 210: control>>A210;
						 clear(c,numint);
						 break;
               case 209: control>>A209;
						 clear(c,numint);
						 break;
				case 211: control>>A211;
						 clear(c,numint);
						 break;
				case 212: control>>A212;
						 clear(c,numint);
						 break;
               case 214: control>>A214;
						 clear(c,numint);
						 break;
               case 215: control>>A215;
						 clear(c,numint);
						 break;
               case 216: control>>A216;
						 clear(c,numint);
						 break;
               case 217: control>>A217;
						 clear(c,numint);
						 break;
               case 218: control>>A218;
						 clear(c,numint);
						 break;
               case 219: control>>A219;
						 clear(c,numint);
						 break;
				case 220: control>>A220;
						 clear(c,numint);
						 break;
				case 221: control>>A221;
						 clear(c,numint);
						 break;
               case 222: control>>A222;
						 clear(c,numint);
						 break;
               case 223: control>>A223;
						 clear(c,numint);
						 break;
				case 230: control>>A230;
						 clear(c,numint);
						 break;
               case 240: control>>A240;
						 clear(c,numint);
						 break;
				case 241: control>>A241;
						 clear(c,numint);
						 break;
				case 242: control>>A242;
						 clear(c,numint);
						 break;
               case 243: control>>A243;
						 clear(c,numint);
						 break;
               case 244: control>>A244_val;
                        A244=1;
						 clear(c,numint);
						 break;
               case 245: control>>A245_val;
                        A245=1;
						 clear(c,numint);
						 break;
               case 246: control>>A246;
						 clear(c,numint);
						 break;
               case 247: control>>A247;
                        clear(c,numint);
						 break;
               case 248: control>>A248;
						 clear(c,numint);
						 break;
               case 249: control>>A249;
						 clear(c,numint);
						 break;
               case 260: control>>A260;
						 clear(c,numint);
						 break;
               case 270: control>>A270;
						 clear(c,numint);
						 break;
               case 300: control>>A300;
						 clear(c,numint);
						 break;
               case 310: control>>A310;
						 clear(c,numint);
						 break;
               case 311: control>>A311;
						 clear(c,numint);
						 break;
               case 312: control>>A312;
						 clear(c,numint);
						 break;
               case 313: control>>A313;
						 clear(c,numint);
						 break;
               case 320: control>>A320;
						 clear(c,numint);
						 break;
               case 321: control>>A321;
						 clear(c,numint);
						 break;
               case 343: control>>A343;
						 clear(c,numint);
						 break;
               case 344: control>>A344_val;
                        A244=1;
						 clear(c,numint);
						 break;
               case 345: control>>A345_val;
                        A245=1;
						 clear(c,numint);
						 break;
               case 346: control>>A346;
						 clear(c,numint);
						 break;
               case 347: control>>A347;
                        clear(c,numint);
						 break;
               case 348: control>>A348;
						 clear(c,numint);
						 break;
               case 349: control>>A349;
						 clear(c,numint);
						 break;
               case 410: control>>A410;
                        clear(c,numint);
                        break;
               case 440: control>>A440;
                        clear(c,numint);
                        break;						

				}
				break;
		case 'B': control>>numint;
				switch(numint)
				{
				case 10: control>>B10;
						 clear(c,numint);
						 break;
                case 19: control>>B19;
						 clear(c,numint);
						 break;
				case 20: control>>B20;
						 clear(c,numint);
						 break;
				case 26: control>>B26;
						 clear(c,numint);
						 break;

				case 28: control>>B28;
						 clear(c,numint);
						 break;
				case 29: control>>B29;
						 clear(c,numint);
						 break;
				case 30: control>>B30;
						 clear(c,numint);
						 break;
				case 50: control>>B50;
						 clear(c,numint);
						 break;
				case 51: control>>B51;
						 clear(c,numint);
						 break;
				case 52: control>>B52;
						 clear(c,numint);
						 break;
				case 53: control>>B53;
						 clear(c,numint);
						 break;
				case 54: control>>B54;
						 clear(c,numint);
						 break;
				case 55: control>>B55;
						 clear(c,numint);
						 break;
				case 56: control>>B56;
						 clear(c,numint);
						 break;
                case 60: control>>B60;
						 clear(c,numint);
						 break;
                case 61: control>>B61;
						 clear(c,numint);
						 break;
                case 62: control>>B62;
						 clear(c,numint);
						 break;
                case 63: control>>B63;
						 clear(c,numint);
						 break;
                case 64: control>>B64;
						 clear(c,numint);
						 break;
                case 65: control>>B65;
						 clear(c,numint);
						 break;
				case 66: control>>B66_1>>B66_2;
						 clear(c,numint);
						 break;
               case 67: ++B67;
						 clear(c,numint);
						 break;
			   case 68: ++B68;
						 clear(c,numint);
						 break;
			   case 69: ++B69;
						 clear(c,numint);
						 break;
			   case 70: ++B70;
						 clear(c,numint);
						 break;
			   case 71: ++B71;
						 clear(c,numint);
						 break;
              case 74: control>>B74;
						 clear(c,numint);
						 break; 
			   case 75: control>>B75;
						 clear(c,numint);
						 break;
			   case 76: control>>B76;
						 clear(c,numint);
						 break;
			   case 77: control>>B77;
						 clear(c,numint);
						 break;
			   case 78: control>>B78;
						 clear(c,numint);
						 break;
			   case 79: control>>B79;
						 clear(c,numint);
						 break;
			   case 80: control>>B80;
						 clear(c,numint);
						 break;
			   case 81: control>>B81_1>>B81_2;
						 B81=1;
						 clear(c,numint);
						 break;
              case 82: control>>B82;
						 clear(c,numint);
						 break;
			   case 83: control>>B83;
						 clear(c,numint);
						 break;
			   case 84: control>>B84;
						 clear(c,numint);
						 break;
              case 85: control>>B85;
						 clear(c,numint);
						 break;
			   case 86: control>>B86;
						 clear(c,numint);
						 break;
			   case 87: control>>B87_1>>B87_2;
                         B87=1;
						 clear(c,numint);
						 break;
			   case 88: control>>B88;
						 clear(c,numint);
						 break;
				case 89: control>>B89;
						 clear(c,numint);
						 break;
               case 90: control>>B90;
						 clear(c,numint);
						 break;
               case 91: control>>B91_1>>B91_2>>B91_3;
                        B91=1;
						 clear(c,numint);
						 break;
               case 92: control>>B92;
						 clear(c,numint);
						 break;
               case 93: control>>B93_1>>B93_2>>B93_3;
                        B93=1;
						 clear(c,numint);
						 break;
               case 96: control>>B96_1>>B96_2>>B96_3;
						 clear(c,numint);
						 break;
               case 97: control>>B97;
						 clear(c,numint);
						 break;
               case 98: control>>B98;
						 clear(c,numint);
						 break;
               case 99: control>>B99;
						 clear(c,numint);
						 break;
               case 101: control>>B101;
						 clear(c,numint);
						 break;
               case 102: control>>B102;
						 clear(c,numint);
						 break;
			   case 103: control>>B103;
						 clear(c,numint);
						 break;
			   case 104: control>>B104;
						 clear(c,numint);
						 break;
			   case 105: control>>B105_1>>B105_2>>B105_3;
						 clear(c,numint);
						 break;
			   case 106: ++B106;
						 clear(c,numint);
						 break;
			   case 107: ++B107;
						 clear(c,numint);
						 break;
              case 108: ++B108;
						 clear(c,numint);
						 break;
			   case 109: control>>B109;
						 clear(c,numint);
						 break;
				case 110: control>>B110_d;
						 B110=1;
						 clear(c,numint);
						 break;
			   case 111: control>>B111_zs>>B111_ze;
						 clear(c,numint);
						 break;
               case 112: control>>B112_zs>>B112_z2>>B112_ze;
						 clear(c,numint);
						 break;
               case 115: control>>B115;
						 clear(c,numint);
						 break;
               case 116: control>>B116;
						 clear(c,numint);
						 break;
               case 117: control>>B117;
						 clear(c,numint);
						 break;
			   case 118: control>>B118;
						 clear(c,numint);
						 break;
			   case 119: control>>B119;
						 clear(c,numint);
						 break;
			   case 120: control>>B120;
						 clear(c,numint);
						 break;
               case 121: control>>B121;
						 clear(c,numint);
						 break;
               case 122: control>>B122;
						 clear(c,numint);
						 break;
               case 123: control>>B123;
						 clear(c,numint);
						 break;
			   case 126: control>>B126;
						 clear(c,numint);
						 break;
               case 130: control>>B130;
						 clear(c,numint);
						 break;
               case 131: control>>B131;
						 clear(c,numint);
						 break;
               case 132: control>>B132_s>>B132_e;
						 clear(c,numint);
						 break;
               case 133: control>>B133;
						 clear(c,numint);
						 break;
               case 134: control>>B134;
						 clear(c,numint);
						 break;
               case 135: control>>B135;
						 clear(c,numint);
						 break;
               case 136: control>>B136;
						 clear(c,numint);
						 break;
               case 140: control>>B140_1>>B140_2>>B140_3;
						 clear(c,numint);
						 break;
               case 160: control>>B160;
						 clear(c,numint);
						 break;
               case 180: control>>B180;
						 clear(c,numint);
						 break;
               case 181: control>>B181_1>>B181_2>>B181_3;
						 clear(c,numint);
						 break;
               case 182: control>>B182_1>>B182_2>>B182_3;
						 clear(c,numint);
						 break;
               case 183: control>>B183_1>>B183_2>>B183_3;
						 clear(c,numint);
						 break;
			   case 191: control>>B191_1>>B191_2>>B191_3>>B191_4;
						 clear(c,numint);
						 B191=1;
						 break;
			   case 192: control>>B192_1>>B192_2>>B192_3>>B192_4;
						 clear(c,numint);
						 B192=1;
						 break;
				case 194: control>>B194_s>>B194_e;
						 clear(c,numint);
						 break;
               case 210: control>>B210;
						 clear(c,numint);
						 break;
			   case 240: ++B240;
						 clear(c,numint);
						 break;
			   case 241: control>>B241;
						 clear(c,numint);
						 break;
			   case 242: control>>B242;
						 clear(c,numint);
						 break;
			   case 243: control>>B243;
						 clear(c,numint);
						 break;
               case 260: control>>B260;
						 clear(c,numint);
						 break;
               case 264: control>>B264;
						 clear(c,numint);
						 break;
               case 267: control>>B267;
						 clear(c,numint);
						 break;
               case 270: ++B270;
						 B269=1;
						 clear(c,numint);
						 break;
               case 274: ++B274;
						 B269=1;
						 clear(c,numint);
						 break;
               case 281: ++B281;
						 B269=1;
						 clear(c,numint);
						 break;
               case 291: ++B291;
						 B269=1;
						 clear(c,numint);
						 break;
               case 295: control>>B295;
						 clear(c,numint);
						 break;
               case 308: control>>B308;
						 clear(c,numint);
						 break;
               case 309: control>>B309;
						 clear(c,numint);
						 break;
               case 310: ++B310;
						 B269=2;
						 clear(c,numint);
						 break;
				}
				break;
				
		case 'C': control>>numint;
				switch(numint)
				{
				case 1: control>>C1;
						 clear(c,numint);
						 break;
				case 2: control>>C2;
						 clear(c,numint);
						 break;
				case 3: control>>C3;
						 clear(c,numint);
						 break;
				case 4: control>>C4;
						 clear(c,numint);
						 break;
				case 5: control>>C5;
						 clear(c,numint);
						 break;
				case 10: control>>C10;
						 clear(c,numint);
						 break;
				case 15: control>>C15;
						 clear(c,numint);
						 break;
				case 20: control>>C20;
						 clear(c,numint);
						 break;
                case 50: control>>C50_1>>C50_2;
						 clear(c,numint);
						 break;
                case 51: control>>C51;
						 clear(c,numint);
						 break;
                case 52: control>>C52;
						 clear(c,numint);
						 break;
                case 53: control>>C53;
						 clear(c,numint);
						 break;
                case 54: control>>C54;
						 clear(c,numint);
						 break;
                case 55: control>>C55;
						 clear(c,numint);
						 break;
                case 56: control>>C56;
						 clear(c,numint);
						 break;
                case 57: control>>C57_1>>C57_2>>C57_3>>C57_4;
						 clear(c,numint);
						 break;
                case 58: control>>C58_1>>C58_2>>C58_3>>C58_4;
						 clear(c,numint);
						 break;
				case 75: ++C75;
						 clear(c,numint);
						 break;

				}
				break;



		case 'D':control>>numint;
				switch(numint)
				{
				case 10: control>>D10;
						 clear(c,numint);
						 break;
				case 11: control>>D11;
						 clear(c,numint);
						 break;
				case 20: control>>D20;
						 clear(c,numint);
						 break;
				case 21: control>>D21;
						 clear(c,numint);
						 break;
				case 22: control>>D22;
						 clear(c,numint);
						 break;		 
				case 23: control>>D23;
						 clear(c,numint);
						 break;
                case 24: control>>D24;
						 clear(c,numint);
						 break;
				case 29: control>>D29;
						 clear(c,numint);
						 break;
				case 30: control>>D30;
						 clear(c,numint);
						 break;
				case 31: control>>D31;
						 clear(c,numint);
						 break;
				case 32: control>>D32;
						 clear(c,numint);
						 break;
				case 33: control>>D33;
						 clear(c,numint);
						 break;
				case 34: control>>D34;
						 clear(c,numint);
						 break;
				case 35: control>>D35;
						 clear(c,numint);
						 break;
                case 36: control>>D36;
						 clear(c,numint);
						 break;
                case 38: control>>D38;
						 clear(c,numint);
						 break;
				}
				break;

		case 'F': control>>numint;
				switch(numint)
				{
				case 10: control>>F10;
						 clear(c,numint);
						 break;
               case 11: control>>F11;
						 clear(c,numint);
						 break;
				case 19: control>>F19;
						 clear(c,numint);
						 break;
				case 30: control>>F30;
						 clear(c,numint);
						 break;
                case 31: control>>F31;
						 clear(c,numint);
						 break;
                case 32: control>>F32;
						 clear(c,numint);
						 break;
                case 33: control>>F33;
						 clear(c,numint);
						 break;
                case 34: control>>F34;
						 clear(c,numint);
						 break;
                case 35: control>>F35;
						 clear(c,numint);
						 break;
				case 36: control>>F36;
						 clear(c,numint);
						 break;
				case 39: control>>F39;
						 clear(c,numint);
						 break;
				case 40: control>>F40;
						 clear(c,numint);
						 break;
                case 41: control>>F41;
						 clear(c,numint);
						 break;
				case 42: control>>F42;
						 clear(c,numint);
						 break;
				case 43: control>>F43;
						 clear(c,numint);
						 break;
				case 44: control>>F44;
						 clear(c,numint);
						 break;
                case 45: control>>F45;
						 clear(c,numint);
						 break;
                case 46: control>>F46;
						 clear(c,numint);
						 break;
                case 47: control>>F47;
						 clear(c,numint);
						 break;
				case 49: control>>F49;
						 clear(c,numint);
						 break;
				case 50: control>>F50;
						 clear(c,numint);
						 break;
				case 51: control>>F51;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 52: control>>F52;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 53: control>>F53;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 54: control>>F54;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 55: control>>F55;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 56: control>>F56;
                        F50_flag=1;
						 clear(c,numint);
						 break;
                case 57: control>>F57_1>>F57_2>>F57_3>>F57_4;
						 clear(c,numint);
						 break;
                case 58: control>>F58_1>>F58_2>>F58_3>>F58_4;
						 clear(c,numint);
						 break;
                case 59: control>>F59_xm>>F59_ym>>F59_zs>>F59_ze>>F59_r;
						 clear(c,numint);
						 break;
                case 60: control>>F60;
						 clear(c,numint);
						 break;
                case 61: control>>F61;
						 clear(c,numint);
						 break;
                case 62: control>>F62;
						 clear(c,numint);
						 break;
                case 63: control>>F63;
						 clear(c,numint);
						 break;
				case 64: control>>F64_xs>>F64_ys>>F64_zs>>F64_alpha;
						 F64=1;
						 clear(c,numint);
						 break;
                case 70: ++F70;
						 clear(c,numint);
						 break;
				case 71: ++F71;
						 clear(c,numint);
						 break;
				case 72: ++F72;
						 clear(c,numint);
						 break;
                case 80: control>>F80;
						 clear(c,numint);
						 break;
                case 84: control>>F84;
						 clear(c,numint);
						 break;
                case 85: control>>F85;
						 clear(c,numint);
						 break;
				case 101: control>>F101;
						 clear(c,numint);
						 break;
                case 150: control>>F150;
						 clear(c,numint);
						 break;
				case 151: control>>F151;
						 clear(c,numint);
						 break;
				case 300: control>>F300;
						 clear(c,numint);
						 break;
				case 305: control>>F305;
						 clear(c,numint);
						 break;
				case 310: control>>F310;
						 clear(c,numint);
						 break;
				case 321: control>>F321;
						 clear(c,numint);
						 break;
				case 322: control>>F322;
						 clear(c,numint);
						 break;
				case 323: control>>F323;
						 clear(c,numint);
						 break;
				case 350: control>>F350;
						 clear(c,numint);
						 break;
				case 360: control>>F360;
						 clear(c,numint);
						 break;
				case 361: control>>F361;
						 clear(c,numint);
						 break;
				case 362: control>>F362;
						 clear(c,numint);
						 break;
			    case 369: ++F369;
						 clear(c,numint);
						 break;
				case 370: ++F370;
						 clear(c,numint);
						 break;
				case 371: ++F371;
						 clear(c,numint);
						 break;
               case 374: ++F374;
						 clear(c,numint);
						 break;
               case 375: ++F375;
						 clear(c,numint);
						 break;
               case 378: ++F378;
						 clear(c,numint);
						 break;
               case 379: ++F379;
						 clear(c,numint);
						 break;
				case 380: control>>F380;
						 clear(c,numint);
						 break;
				case 381: control>>F381;
						 clear(c,numint);
						 break;
				case 382: control>>F382;
						 clear(c,numint);
						 break;
				case 390: ++F390;
						 clear(c,numint);
						 break;
				case 391: ++F391;
						 clear(c,numint);
						 break;
               case 394: ++F394;
						 clear(c,numint);
						 break;
               case 395: ++F395;
						 clear(c,numint);
						 break;
               case 398: ++F398;
						 clear(c,numint);
						 break;
               case 399: ++F399;
						 clear(c,numint);
						 break;
				}
				break;

		case 'G':control>>numint;
				switch(numint)
				{
				case 10: control>>G10;
						 clear(c,numint);
						 break;
				case 11: control>>G11;
						 clear(c,numint);
						 break;
				case 12: control>>G12;
						 clear(c,numint);
						 break;
				case 20: control>>G20;
						 clear(c,numint);
						 break;
				case 21: control>>G21;
						 clear(c,numint);
						 break;
				case 22: control>>G22;
						 clear(c,numint);
						 break;
				case 30: control>>G30;
						 clear(c,numint);
						 break;
                case 40: control>>G40;
						 clear(c,numint);
						 break;
                case 50: control>>G50;
						 clear(c,numint);
						 break;
                case 52: control>>G52;
						 clear(c,numint);
						 break;
                case 60: ++G60;
						 clear(c,numint);
						 break;
                case 61: ++G61;
						 clear(c,numint);
						 break;
				case 81: ++G81;
						 clear(c,numint);
						 break;
				case 95: ++G95;
						 clear(c,numint);
						 break;
				}
				break;

        case 'H': control>>numint;
				switch(numint)
				{
				case 10: control>>H10;
						 clear(c,numint);
						 break;
                case 50: control>>H50_1>>H50_2;
						 clear(c,numint);
						 break;
                case 51: control>>H51;
						 clear(c,numint);
						 break;
                case 52: control>>H52;
						 clear(c,numint);
						 break;
                case 53: control>>H53;
						 clear(c,numint);
						 break;
                case 54: control>>H54;
						 clear(c,numint);
						 break;
                case 55: control>>H55;
						 clear(c,numint);
						 break;
                case 56: control>>H56;
						 clear(c,numint);
						 break;
                case 57: control>>H57_1>>H57_2>>H57_3>>H57_4;
						 clear(c,numint);
						 break;
                case 58: control>>H58_1>>H58_2>>H58_3>>H58_4;
						 clear(c,numint);
						 break;

				}
				break;

		case 'I': control>>numint;
				switch(numint)
				{
				case 10: control>>I10;
						 clear(c,numint);
						 break;
                case 11: control>>I11;
						 clear(c,numint);
						 break;
                case 12: control>>I12;
						 clear(c,numint);
						 break;
                case 13: control>>I13;
						 clear(c,numint);
						 break;
                case 20: control>>I20;
						 clear(c,numint);
						 break;
                case 21: control>>I21;
						 clear(c,numint);
						 break;
				 case 30: control>>I30;
						 clear(c,numint);
						 break;
				 case 40: control>>I40;
						 clear(c,numint);
						 break;
				 case 41: control>>I41;
						 clear(c,numint);
						 break;
                case 55: control>>I55;
						 clear(c,numint);
						 break;
                case 56: control>>I56;
						 clear(c,numint);
						 break;
                case 58: control>>I58_1>>I58_2;
						 clear(c,numint);
						 break;
                case 230: control>>I230;
						 clear(c,numint);
						 break;
                case 231: control>>I231;
						 clear(c,numint);
						 break;
                case 232: control>>I232;
						 clear(c,numint);
						 break;
                case 240: control>>I240;
						 clear(c,numint);
						 break;
                case 241: control>>I241;
						 clear(c,numint);
						 break;
                case 242: control>>I242;
						 clear(c,numint);
						 break;
				}
				break;

        case 'M': control>>numint;
				switch(numint)
				{
				case 10: control>>M10;
						 clear(c,numint);
						 break;

				}
				break;


		case 'N': control>>numint;
				switch(numint)
				{
				case  5: control>>N5;
						 clear(c,numint);
						 break;
               case  8: control>>N8;
						 clear(c,numint);
						 break;
               case  9: control>>N9;
						 clear(c,numint);
						 break;
				case 10: control>>N10;
						 clear(c,numint);
						 break;
                case 11: control>>N11;
						 clear(c,numint);
						 break;
                case 12: control>>N12;
						 clear(c,numint);
						 break;
                case 13: control>>N13;
						 clear(c,numint);
						 break;
                case 14: control>>N14;
						 clear(c,numint);
						 break;
				case 15: control>>N15;
						 clear(c,numint);
						 break;
				case 16: control>>N16;
						 clear(c,numint);
						 break;
				case 17: control>>N17;
						 clear(c,numint);
						 break;
				case 18: control>>N18;
						 clear(c,numint);
						 break;
				case 40: control>>N40;
						 clear(c,numint);
						 break;
				case 41: control>>N41;
						 clear(c,numint);
						 break;
				case 42: control>>N42;
						 clear(c,numint);
						 break;
				case 43: control>>N43;
						 clear(c,numint);
						 break;
				case 44: control>>N44;
						 clear(c,numint);
					     break;
				case 45: control>>N45;
						 clear(c,numint);
					     break;
				case 46: control>>N46;
						 clear(c,numint);
						 break;
				case 47: control>>N47;
						 clear(c,numint);
						 break;
               case 48: control>>N48;
						 clear(c,numint);
						 break;
				case 49: control>>N49;
						 clear(c,numint);
						 break;
				case 50: control>>N50;
						 clear(c,numint);
						 break;
               case 51: control>>N51;
						 clear(c,numint);
						 break;
               case 52: control>>N52;
						 clear(c,numint);
						 break;
               case 53: control>>N53;
						 clear(c,numint);
						 break;
               case 54: control>>N54;
						 clear(c,numint);
						 break;
               case 55: control>>N55;
						 clear(c,numint);
						 break;
               case 56: control>>N56;
						 clear(c,numint);
						 break;
               case 57: control>>N57_1>>N57_2>>N57_3;
						 clear(c,numint);
						 break;
               case 58: control>>N58;
						 clear(c,numint);
						 break;
               case 60: control>>N60;
						 clear(c,numint);
						 break;
               case 61: control>>N61;
						 clear(c,numint);
						 break;
               case 71: control>>N71;
						 clear(c,numint);
						 break;
               case 72: control>>N72;
						 clear(c,numint);
						 break;
               case 73: control>>N73;
						 clear(c,numint);
						 break;
				}
				break;

		case 'P': control>>numint;
				switch(numint)
				{
				case 10: control>>P10;
						 clear(c,numint);
						 break;
				case 11: control>>P11;
						 clear(c,numint);
						 break;
               case 12: control>>P12;
						 clear(c,numint);
						 break;
				case 14: control>>P14;
						 clear(c,numint);
						 break;
                case 15: control>>P15;
						 clear(c,numint);
						 break;
				case 17: control>>P17;
						 clear(c,numint);
						 break;
				case 18: control>>P18;
						 clear(c,numint);
						 break;
				case 19: control>>P19;
						 clear(c,numint);
						 break;
				case 20: control>>P20;
						 clear(c,numint);
						 break;
				case 23: control>>P23;
						 clear(c,numint);
						 break;
                case 24: control>>P24;
						 clear(c,numint);
						 break;
                case 25: control>>P25;
						 clear(c,numint);
						 break;
				case 26: control>>P26;
						 clear(c,numint);
						 break;
				case 27: control>>P27;
						 clear(c,numint);
						 break;
				case 28: control>>P28;
						 clear(c,numint);
						 break;
				case 29: control>>P29;
						 clear(c,numint);
						 break;
				case 30: control>>P30;
						 clear(c,numint);
						 break;
				case 34: control>>P34;
						 clear(c,numint);
						 break;
                case 35: ++P35;
						 clear(c,numint);
						 break;
                case 40: control>>P40;
						 clear(c,numint);
						 break;
                case 41: control>>P41;
						 clear(c,numint);
						 break;
				 case 42: control>>P42;
						 clear(c,numint);
						 break;
                case 50: ++P50;
						 clear(c,numint);
						 break;
				case 51: ++P51;
						 clear(c,numint);
						 break;
                case 52: ++P52;
						 clear(c,numint);
						 break;
				case 53: control>>P53;
						 clear(c,numint);
						 break;
				case 54: control>>P54;
						 clear(c,numint);
						 break;
				case 55: control>>P55;
						 clear(c,numint);
						 break;
				case 56: ++P56;
						 clear(c,numint);
						 break;
				case 59: control>>P59;
						 clear(c,numint);
						 break;
				case 61: ++P61;
						 clear(c,numint);
						 break;
				case 62: ++P62;
						 clear(c,numint);
						 break;
				case 66: control>>P66;
						 clear(c,numint);
						 break;
				case 67: ++P67;
						 clear(c,numint);
						 break;
                case 71: control>>P71;
						 clear(c,numint);
						 break;
                case 75: control>>P75;
						 clear(c,numint);
						 break;
                case 78: control>>P78;
						 clear(c,numint);
						 break;
			    case 79: control>>P79;
						 clear(c,numint);
						 break;
                case 81: ++P81;
						 clear(c,numint);
						 break;
                case 82: control>>P82_x>>P82_y;
                         clear(c,numint);
						  break;
				case 83: control>>P83;
						 clear(c,numint);
						 break;
				case 84: control>>P84;
						 clear(c,numint);
						 break;
				case 85: ++P85;
						 clear(c,numint);
						 break;
                case 86: control>>P86_x>>P86_y;
                         clear(c,numint);
						  break;
				case 87: control>>P87;
						 clear(c,numint);
						 break;
				case 88: control>>P88;
						 clear(c,numint);
						 break;
				case 89: control>>P89_cm>>P89_cd;
						 clear(c,numint);
						 break;
				case 90: control>>P90;
						 clear(c,numint);
						 break;
				case 91: control>>P91;
						 clear(c,numint);
						 break;
               case 92: control>>P92;
						 clear(c,numint);
						 break;
                case 93: control>>P93;
						 clear(c,numint);
						 break;
				case 101: control>>P101_xm>>P101_ym>>P101_zs>>P101_ze>>P101_r1>>P101_r2;
					      P101=1;
                          clear(c,numint);
						  break;
				case 121: ++P121;
						 clear(c,numint);
						 break;
				case 122: control>>P122;
						 clear(c,numint);
						 break;
			    case 123: ++P123;
						 clear(c,numint);
						 break;
				case 124: ++P124;
						 clear(c,numint);
						 break;
				case 125: ++P125;
						 clear(c,numint);
						 break;
				case 126: control>>P126;
						 clear(c,numint);
						 break;
				case 151: control>>P151;
						 clear(c,numint);
						 break;
				case 152: control>>P152;
						 clear(c,numint);
						 break;
				case 180: control>>P180;
						 clear(c,numint);
						 break;
				case 181: control>>P181;
						 clear(c,numint);
						 break;
				case 182: control>>P182;
						 clear(c,numint);
						 break;
               case 191: control>>P191;
						 clear(c,numint);
						 break;
               case 210: control>>P210;
						 clear(c,numint);
						 break;
				case 211: control>>P211;
						 clear(c,numint);
						 break;
				case 212: control>>P212;
						 clear(c,numint);
						 break;
               case 230: ++P230;
						 clear(c,numint);
						 break;
                case 240: ++P240;
						 clear(c,numint);
						 break;
				case 351: ++P351;
						 clear(c,numint);
						 break;
				case 352: ++P352;
						 clear(c,numint);
						 break;
				}
				break;

        case 'S': control>>numint;
				switch(numint)
				{
				case 10: control>>S10;
						 clear(c,numint);
						 break;
                case 11: control>>S11;
						 clear(c,numint);
						 break;
                case 12: control>>S12;
						 clear(c,numint);
						 break;
                case 13: control>>S13;
						 clear(c,numint);
						 break;
                case 14: control>>S14;
						 clear(c,numint);
						 break;
                case 15: control>>S15;
						 clear(c,numint);
						 break;
                case 16: control>>S16;
						 clear(c,numint);
						 break;
                case 17: control>>S17;
						 clear(c,numint);
						 break;
                case 18: control>>S18;
						 clear(c,numint);
						 break;
				case 19: control>>S19;
						 clear(c,numint);
						 break;
				case 20: control>>S20;
						 clear(c,numint);
						 break;
				case 21: control>>S21;
						 clear(c,numint);
						 break;
                case 22: control>>S22;
						 clear(c,numint);
						 break;
                case 23: control>>S23;
						 clear(c,numint);
						 break;
                case 24: control>>S24;
						 clear(c,numint);
						 break;
                case 25: control>>S25;
						 clear(c,numint);
						 break;
			    case 28: control>>S28;
						 clear(c,numint);
						 break;
				case 29: control>>S29;
						 clear(c,numint);
						 break;
                case 30: control>>S30;
						 clear(c,numint);
						 break;
                case 31: control>>S31;
						 clear(c,numint);
						 break;
				case 37: control>>S37;
						 clear(c,numint);
						 break;
				case 38: control>>S38;
						 clear(c,numint);
						 break;
				case 39: control>>S39;
						 clear(c,numint);
						 break;
                case 41: control>>S41;
						 clear(c,numint);
						 break;
			    case 42: control>>S42;
						 clear(c,numint);
						 break;
                case 43: control>>S43;
						 clear(c,numint);
						 break;
                case 44: control>>S44;
						 clear(c,numint);
						 break;
				 case 45: control>>S45;
						 clear(c,numint);
						 break;
				 case 46: control>>S46;
						 clear(c,numint);
						 break;
				 case 47: control>>S47;
						 clear(c,numint);
						 break;
				 case 48: control>>S48;
						 clear(c,numint);
						 break;		 
                case 50: control>>S50;
						 clear(c,numint);
						 break;
                case 57: control>>S57;
						 clear(c,numint);
						 break;
                case 60: control>>S60;
						 clear(c,numint);
						 break;
                case 71: control>>S71;
						 clear(c,numint);
						 break;
                case 72: control>>S72;
						 clear(c,numint);
						 break;
				 case 73: ++S73;
						 clear(c,numint);
						 break;
                case 77: control>>S77_xs>>S77_xe;
                          S77=1;
						 clear(c,numint);
						 break;
                case 80: control>>S80;
						 clear(c,numint);
						 break;
                case 81: control>>S81;
						 clear(c,numint);
						 break;
                case 82: control>>S82;
						 clear(c,numint);
						 break;
                case 90: control>>S90;
						 clear(c,numint);
						 break;
                case 91: control>>S91;
						 clear(c,numint);
						 break;
				 case 92: control>>S92;
						 clear(c,numint);
						 break;
                case 93: control>>S93;
						 clear(c,numint);
						 break;
				case 100: control>>S100;
						 clear(c,numint);
						 break;
				case 101: control>>S101;
						 clear(c,numint);
						 break;
               case 102: control>>S102;
						 clear(c,numint);
						 break;
               case 103: control>>S103;
						 clear(c,numint);
						 break;
                case 116: control>>S116;
						 clear(c,numint);
						 break;
                case 117: control>>S117;
						 clear(c,numint);
						 break;
				}
				break;

		case 'T': control>>numint;
				switch(numint)
				{
				case 10: control>>T10;
						 clear(c,numint);
						 break;
                case 11: control>>T11;
						 clear(c,numint);
						 break;
                case 12: control>>T12;
						 clear(c,numint);
						 break;
				case 13: control>>T13;
						 clear(c,numint);
						 break;
                case 30: control>>T30;
						 clear(c,numint);
						 break;
                case 31: control>>T31;
						 clear(c,numint);
						 break;
				case 32: control>>T32;
						 clear(c,numint);
						 break;
				case 35: control>>T35;
						 clear(c,numint);
						 break;
				case 36: control>>T36;
						 clear(c,numint);
						 break;
				case 37: control>>T37;
						 clear(c,numint);
						 break;
               case 38: control>>T38;
						 clear(c,numint);
						 break;
               case 39: control>>T39;
						 clear(c,numint);
						 break;
                case 40: control>>T40;
						 clear(c,numint);
						 break;
				case 41: control>>T41;
						 clear(c,numint);
						 break;
				case 42: control>>T42;
						 clear(c,numint);
						 break;
				case 43: control>>T43;
						 clear(c,numint);
						 break;
                case 51: control>>T51;
						 clear(c,numint);
						 break;
				case 52: control>>T52;
						 clear(c,numint);
						 break;
				case 53: control>>T53;
						 clear(c,numint);
						 break;
				}
				break;

		case 'W': control>>numint;
				switch(numint)
				{
				case  1: control>>W1;
						 clear(c,numint);
						 break;
				case  2: control>>W2;
						 clear(c,numint);
						 break;
				case  3: control>>W3;
						 clear(c,numint);
						 break;
				case  4: control>>W4;
						 clear(c,numint);
						 break;
				case  5: control>>W5;
						 clear(c,numint);
						 break;
				case  6: control>>W6;
						 clear(c,numint);
						 break;
				case  7: control>>W7;
						 clear(c,numint);
						 break;
				case 10: control>>W10;
						 clear(c,numint);
						 break;
				case 20: control>>W20;
						 clear(c,numint);
						 break;
				case 21: control>>W21;
						 clear(c,numint);
						 break;
				case 22: control>>W22;
						 clear(c,numint);
						 break;
				case 30: control>>W30;
						 clear(c,numint);
						 break;
				case 31: control>>W31;
						 clear(c,numint);
						 break;
                case 90: control>>W90;
						 clear(c,numint);
						 break;
                case 95: control>>W95;
						 clear(c,numint);
						 break;
                case 96: control>>W96;
						 clear(c,numint);
						 break;
                case 97: control>>W97;
						 clear(c,numint);
						 break;
                case 98: control>>W98;
						 clear(c,numint);
						 break;
                case 101: control>>W101;
						 clear(c,numint);
						 break;
                case 102: control>>W102_phi>>W102_c;
						 clear(c,numint);
						 break;
                case 103: control>>W103;
						 clear(c,numint);
						 break;
                case 104: control>>W104;
						 clear(c,numint);
						 break;
                case 110: control>>W110;
						 clear(c,numint);
						 break;
                case 111: control>>W111;
						 clear(c,numint);
						 break;
                case 112: control>>W112;
						 clear(c,numint);
						 break;
				}
				break;
				
		case 'X': control>>numint;
				switch(numint)
				{
				case  10: control>>X10;
						 clear(c,numint);
						 break;
				case  11: control>>X11_u>>X11_v>>X11_w>>X11_p>>X11_q>>X11_r;
						 clear(c,numint);
						 break;
				case  12: control>>X12;
						 clear(c,numint);
						 break;
				case  13: control>>X13;
						 clear(c,numint);
						 break;
               case  18: control>>X18;
						 clear(c,numint);
						 break;
				case  19: control>>X19;
						 clear(c,numint);
						 break;
				case  21: control>>X21_d;
						 X21=1;
						 clear(c,numint);
						 break;
				case  22: control>>X22_m;
						 X22=1;
						 clear(c,numint);
						 break;
				case  23: control>>X23_x>>X23_y>>X23_z;
						 X23=1;
						 clear(c,numint);
						 break;
				case  24: control>>X24_Ix>>X24_Iy>>X24_Iz;
						 X24=1;
						 clear(c,numint);
						 break;
				case  25: control>>X25_Cp>>X25_Cq>>X25_Cr;
						 clear(c,numint);
						 break;
                case  26: control>>X26_Ku>>X26_Kv>>X26_Kw;
						 clear(c,numint);
						 break;
                case  27: control>>X27_x>>X27_y>>X27_z;
                          X27=1;
						 clear(c,numint);
						 break;
			    case  31: control>>X31;
						 clear(c,numint);
						 break;
				case  32: control>>X32;
						 clear(c,numint);
						 break;
				case  33: control>>X33;
						 clear(c,numint);
						 break;
                case  34: control>>X34;
						 clear(c,numint);
						 break;
				case  38: control>>X38;
						 clear(c,numint);
						 break;
				case  40: control>>X40;
						 clear(c,numint);
						 break;
               case  41: control>>X41;
						 clear(c,numint);
						 break;
				case  100: control>>X100_x>>X100_y>>X100_z;
						 X100=1;
						 clear(c,numint);
						 break;
				case  101: control>>X101_phi>>X101_theta>>X101_psi;
						 X101=1;
						 clear(c,numint);
						 break;
				case  102: control>>X102_u>>X102_v>>X102_w;
						 X102=1;
						 clear(c,numint);
						 break;
				case  103: control>>X103_p>>X103_q>>X103_r;
						 X103=1;
						 clear(c,numint);
						 break;
				case  110: ++X110;
						 clear(c,numint);
						 break;
				case  120: control>>X120_rad>>X120_xc>>X120_yc>>X120_zc;
						 X120=1;
						 clear(c,numint);
						 break;
				case  131: control>>X131_rad>>X131_h>>X131_xc>>X131_yc>>X131_zc;
						 X131=1;
						 clear(c,numint);
						 break;
				case  132: control>>X132_rad>>X132_h>>X132_xc>>X132_yc>>X132_zc;
						 X132=1;
						 clear(c,numint);
						 break;
				case  133: control>>X133_rad>>X133_h>>X133_xc>>X133_yc>>X133_zc;
						 X133=1;
						 clear(c,numint);
						 break;
				case  153: control>>X153_xs>>X153_xe>>X153_ys>>X153_ye>>X153_zs>>X153_ze;
						 X153=1;
						 clear(c,numint);
						 break;
                case  163: ++X163;
						 clear(c,numint);
						 break;
                case  164: ++X164;
						 clear(c,numint);
						 break;
                case  180: control>>X180;
						 clear(c,numint);
						 break;
                case  181: control>>X181;
						 clear(c,numint);
						 break;
                case  182: control>>X182_x>>X182_y>>X182_z;
                          X182=1;
						 clear(c,numint);
						 break;
                case  183: control>>X183_x>>X183_y>>X183_z>>X183_phi>>X183_theta>>X183_psi;
                          X183=1;
						 clear(c,numint);
						 break;
				case  210: control>>X210_u>>X210_v>>X210_w;
						 X210=1;
						 clear(c,numint);
						 break;
				case  211: control>>X211_p>>X211_q>>X211_r;
						 X211=1;
						 clear(c,numint);
						 break;
                case  221: control>>X221_xs>>X221_xe>>X221_ys>>X221_ye>>X221_zs>>X221_ze;
						 X221=1;
						 clear(c,numint);
						 break;
				case  310: control>>X310;
						 clear(c,numint);
						 break;	
               case  311: ++X311;
						 clear(c,numint);
						 break;
				case  320: control>>X320;
						 clear(c,numint);
						 break;
				}
				break;
				
		case 'Y': control>>numint;
				switch(numint)
				{
               case 40: control>>Y40;
						 clear(c,numint);
						 break;
				case 50: control>>Y50;
						 clear(c,numint);
						 break;
				case 60: control>>Y60;
						 clear(c,numint);
						 break;
               case 71: control>>Y71;
						 clear(c,numint);
						 break;
               case 72: control>>Y72;
						 clear(c,numint);
						 break;
               case 73: control>>Y73;
						 clear(c,numint);
						 break;
               case 74: control>>Y74;
						 clear(c,numint);
						 break;

				}
				break;
        
		}
        
        ++count;
        		
	}
        if(count>1e7)
        {
        cout<<endl;
        cout<<"!!! missing input parameter in ctrl.txt !!!"<<endl<<endl;
        cout<<"!!! please check the REEF3D User Guide !!!"<<endl<<endl<<endl<<endl;
        
        exit(0);
        }
	}
	control.close();
	control.clear();
	

    // re-read
	
	// B
	Darray(B67_val,B67);
	Darray(B67_dist,B67);
	Darray(B67_b,B67);
	Darray(B67_x,B67);
	Darray(B67_y,B67);
	
	Darray(B68_val,B68);
	Darray(B68_dist,B68);
	Darray(B68_b,B68);
	Darray(B68_x,B68);
	Darray(B68_y,B68);
	
	Darray(B69_val,B69);
	Darray(B69_dist,B69);
	Darray(B69_b,B69);
	Darray(B69_x,B69);
	Darray(B69_y,B69);
	
	Darray(B70_val,B70);
	Darray(B70_dist,B70);
	Darray(B70_b,B70);
	Darray(B70_x,B70);
	Darray(B70_y,B70);
	
	Darray(B71_val,B71);
	Darray(B71_dist,B71);
	Darray(B71_b,B71);
	Darray(B71_x,B71);
	Darray(B71_y,B71);
	
	Darray(B106_b,B106);
	Darray(B106_x,B106);
	Darray(B106_y,B106);
	
	Darray(B107_xs,B107);
    Darray(B107_xe,B107);
	Darray(B107_ys,B107);
    Darray(B107_ye,B107);
    Darray(B107_d,B107);
    
    Darray(B108_xs,B108);
    Darray(B108_xe,B108);
	Darray(B108_ys,B108);
    Darray(B108_ye,B108);
    Darray(B108_d,B108);
	
	Darray(B240_C,B240);
	Darray(B240_D,B240);
	Darray(B240_xs,B240);
	Darray(B240_xe,B240);
	Darray(B240_ys,B240);
	Darray(B240_ye,B240);
	Darray(B240_zs,B240);
	Darray(B240_ze,B240);
    
    Darray(B270_xs,B270);
	Darray(B270_xe,B270);
	Darray(B270_ys,B270);
	Darray(B270_ye,B270);
	Darray(B270_zs,B270);
	Darray(B270_ze,B270);
    Darray(B270_n,B270);
    Darray(B270_d50,B270);
	Darray(B270_alpha,B270);
	Darray(B270_beta,B270);
    
	Darray(B274_xc,B274);
	Darray(B274_yc,B274);
	Darray(B274_zs,B274);
	Darray(B274_ze,B274);
	Darray(B274_r,B274);
    Darray(B274_n,B274);
    Darray(B274_d50,B274);
	Darray(B274_alpha,B274);
	Darray(B274_beta,B274);
    
    Darray(B281_xs,B281);
	Darray(B281_xe,B281);
	Darray(B281_ys,B281);
	Darray(B281_ye,B281);
	Darray(B281_zs,B281);
	Darray(B281_ze,B281);
    Darray(B281_n,B281);
    Darray(B281_d50,B281);
	Darray(B281_alpha,B281);
	Darray(B281_beta,B281);
    
    Darray(B291_xs,B291);
	Darray(B291_xe,B291);
	Darray(B291_ys,B291);
	Darray(B291_ye,B291);
	Darray(B291_zs,B291);
	Darray(B291_ze,B291);
    Darray(B291_d,B291);
    Darray(B291_n,B291);
    Darray(B291_d50,B291);
	Darray(B291_alpha,B291);
	Darray(B291_beta,B291);
    
    Darray(B310_xs,B310);
	Darray(B310_xe,B310);
	Darray(B310_ys,B310);
	Darray(B310_ye,B310);
	Darray(B310_zs,B310);
	Darray(B310_ze,B310);
    Darray(B310_N,B310);
    Darray(B310_D,B310);
	Darray(B310_Cd,B310);
	
	// C
	Darray(C75_x,C75);
	Darray(C75_z,C75);
	Darray(C75_a,C75);
	Darray(C75_s,C75);
	Darray(C75_l,C75);
	Darray(C75_v,C75);
	

    // F
	Darray(F70_xs,F70);
	Darray(F70_xe,F70);
	
	Darray(F70_ys,F70);
	Darray(F70_ye,F70);
	
	Darray(F70_zs,F70);
	Darray(F70_ze,F70);


	Darray(F71_xs,F71);
	Darray(F71_xe,F71);
	
	Darray(F71_ys,F71);
	Darray(F71_ye,F71);
	
	Darray(F71_zs,F71);
	Darray(F71_ze,F71);
	
	
	Darray(F72_xs,F72);
	Darray(F72_xe,F72);
	
	Darray(F72_ys,F72);
	Darray(F72_ye,F72);
	
	Darray(F72_h,F72);
    
    
    Darray(F369_x,F369);
	Darray(F369_z,F369);
	Darray(F369_a,F369);
	Darray(F369_s,F369);
	Darray(F369_l,F369);
	Darray(F369_v,F369);	
	
	Darray(F370_xs,F370);
	Darray(F370_xe,F370);
	
	Darray(F370_ys,F370);
	Darray(F370_ye,F370);
	
	Darray(F370_zs,F370);
	Darray(F370_ze,F370);
	
	
	Darray(F371_xs,F371);
	Darray(F371_xe,F371);
	
	Darray(F371_ys,F371);
	Darray(F371_ye,F371);
	
	Darray(F371_zs,F371);
	Darray(F371_ze,F371);
    
    Darray(F374_xc,F374);
	Darray(F374_zc,F374);
    Darray(F374_r,F374);
    
    Darray(F375_xc,F375);
	Darray(F375_zc,F375);
    Darray(F375_r,F375);
    
    Darray(F378_xc,F378);
    Darray(F378_yc,F378);
	Darray(F378_zc,F378);
    Darray(F378_r,F378);
    
    Darray(F379_xc,F379);
    Darray(F379_yc,F379);
	Darray(F379_zc,F379);
    Darray(F379_r,F379);
	

	Darray(F390_xs,F390);
	Darray(F390_xe,F390);
	
	Darray(F390_ys,F390);
	Darray(F390_ye,F390);
	
	Darray(F390_zs,F390);
	Darray(F390_ze,F390);
	
	
	Darray(F391_xs,F391);
	Darray(F391_xe,F391);
	
	Darray(F391_ys,F391);
	Darray(F391_ye,F391);
	
	Darray(F391_zs,F391);
	Darray(F391_ze,F391);
    
    Darray(F394_xc,F394);
	Darray(F394_zc,F394);
    Darray(F394_r,F394);
    
    Darray(F395_xc,F395);
	Darray(F395_zc,F395);
    Darray(F395_r,F395);
    
    Darray(F398_xc,F398);
    Darray(F398_yc,F398);
	Darray(F398_zc,F398);
    Darray(F398_r,F398);
    
    Darray(F399_xc,F399);
    Darray(F399_yc,F399);
	Darray(F399_zc,F399);
    Darray(F399_r,F399);
	

	// G
	Darray(G60_xs,G60);
	Darray(G60_xe,G60);
	
	Darray(G60_ys,G60);
	Darray(G60_ye,G60);
	
	Darray(G60_zs,G60);
	Darray(G60_ze,G60);

	
	Darray(G61_xs,G61);
	Darray(G61_xe,G61);
	
	Darray(G61_ys,G61);
	Darray(G61_ye,G61);
	
	Darray(G61_zs,G61);
	Darray(G61_ze,G61);
	
	
	Darray(G81_xs,G81);
	Darray(G81_xe,G81);
	
	Darray(G81_ys,G81);
	Darray(G81_ye,G81);
	
	Darray(G81_zs,G81);
	Darray(G81_ze,G81);
	
	
	Darray(G95_xs,G95);
	Darray(G95_xe,G95);
	
	Darray(G95_ys,G95);
	Darray(G95_ye,G95);
	
	Darray(G95_zs,G95);
	Darray(G95_ze,G95);

    // P
	Darray(P35_ts,P35);
	Darray(P35_te,P35);
	Darray(P35_dt,P35);
	
	Darray(P50_x,P50);
	Darray(P50_y,P50);
	
	Darray(P51_x,P51);
	Darray(P51_y,P51);
	
	Darray(P52_y,P52);
	Darray(P56_x,P56);
	
	Darray(P61_x,P61);
	Darray(P61_y,P61);
	Darray(P61_z,P61);
	
	Darray(P62_xs,P62);
	Darray(P62_ys,P62);
	Darray(P62_zs,P62);
	Darray(P62_xe,P62);
	Darray(P62_ye,P62);
	Darray(P62_ze,P62);
	
	Darray(P67_x,P67);
	
	Darray(P81_xs,P81);
	Darray(P81_ys,P81);
	Darray(P81_zs,P81);
	Darray(P81_xe,P81);
	Darray(P81_ye,P81);
	Darray(P81_ze,P81);
	
	Darray(P85_xs,P85);
	Darray(P85_ys,P85);
	Darray(P85_zs,P85);
	Darray(P85_xe,P85);
	Darray(P85_ye,P85);
	Darray(P85_ze,P85);
	
	Darray(P121_x,P121);
	Darray(P121_y,P121);
	
	Darray(P123_y,P123);
	
	Darray(P124_x,P124);
	
	Darray(P125_x,P125);
	Darray(P125_y,P125);
    
    Darray(P230_x,P230);
    Darray(P240_x,P240);
	
	Darray(P351_x,P351);
	Darray(P351_y,P351);
	Darray(P352_x,P352);
	Darray(P352_y,P352);
	
	// S
	Darray(S73_val,S73);
	Darray(S73_dist,S73);
	Darray(S73_b,S73);
	Darray(S73_x,S73);
	Darray(S73_y,S73);	
	
	// X
	Darray(X110_xs,X110);
	Darray(X110_ys,X110);
	Darray(X110_zs,X110);
	Darray(X110_xe,X110);
	Darray(X110_ye,X110);
	Darray(X110_ze,X110);
    
    Darray(X163_x1,X163);
    Darray(X163_y1,X163);
    Darray(X163_z1,X163);
    Darray(X163_x2,X163);
    Darray(X163_y2,X163);
    Darray(X163_z2,X163);
    Darray(X163_x3,X163);
    Darray(X163_y3,X163);
    Darray(X163_z3,X163);
    Darray(X163_x4,X163);
    Darray(X163_y4,X163);
    Darray(X163_z4,X163);
    Darray(X163_x5,X163);
    Darray(X163_y5,X163);
    Darray(X163_z5,X163);
    Darray(X163_x6,X163);
    Darray(X163_y6,X163);
    Darray(X163_z6,X163);
    
    Darray(X164_x1,X164);
    Darray(X164_y1,X164);
    Darray(X164_z1,X164);
    Darray(X164_x2,X164);
    Darray(X164_y2,X164);
    Darray(X164_z2,X164);
    Darray(X164_x3,X164);
    Darray(X164_y3,X164);
    Darray(X164_z3,X164);
    Darray(X164_x4,X164);
    Darray(X164_y4,X164);
    Darray(X164_z4,X164);
    Darray(X164_x5,X164);
    Darray(X164_y5,X164);
    Darray(X164_z5,X164);
    Darray(X164_x6,X164);
    Darray(X164_y6,X164);
    Darray(X164_z6,X164);
    Darray(X164_x7,X164);
    Darray(X164_y7,X164);
    Darray(X164_z7,X164);
    Darray(X164_x8,X164);
    Darray(X164_y8,X164);
    Darray(X164_z8,X164);
    
    Darray(X311_xs,X311);
	Darray(X311_ys,X311);
	Darray(X311_zs,X311);
	Darray(X311_xe,X311);
	Darray(X311_ye,X311);
	Darray(X311_ze,X311);
	Darray(X311_w,X311); 
	Darray(X311_rho_c,X311); 
	Darray(X311_EA,X311); 
	Darray(X311_d,X311);  
	Darray(X311_l,X311); 
	Darray(X311_H,X311); 
	Darray(X311_P,X311); 
	Darray(X311_facT,X311);
	mooring_count = X311;	

    int countB67=0;
	int countB68=0;
	int countB69=0;
	int countB70=0;
	int countB71=0;
	int countB106=0;
	int countB107=0;
    int countB108=0;
	int countB240=0;
    int countB270=0;
    int countB274=0;
    int countB281=0;
    int countB291=0;
    int countB310=0;
    int countC75=0;
	int countF70=0;
	int countF71=0;
	int countF72=0;
    int countF369=0;
	int countF370=0;
	int countF371=0;
	int countF374=0;
    int countF375=0;
    int countF378=0;
    int countF379=0;
	int countF390=0;
	int countF391=0;
    int countF394=0;
    int countF395=0;
    int countF398=0;
    int countF399=0;
	int countG60=0;
	int countG61=0;
	int countG81=0;
	int countG95=0;
	int countP35=0;
    int countP50=0;
	int countP51=0;
    int countP52=0;
	int countP56=0;
	int countP61=0;
	int countP62=0;
	int countP67=0;
	int countP81=0;
	int countP85=0;
	int countP121=0;
	int countP123=0;
	int countP124=0;
	int countP125=0;
    int countP230=0;
    int countP240=0;
	int countP351=0;
	int countP352=0;
	int countS73=0;
	int countX110=0;
    int countX163=0;
    int countX164=0;
    int countX311=0;

	control.open("ctrl.txt", ios_base::in);
	while(!control.eof())
	{
		control>>c;
		switch(c)
		{
			case 'B': control>>numint;
				switch(numint)
				{
				case 67: control>>B67_val[countB67]>>B67_dist[countB67]>>B67_b[countB67]>>B67_x[countB67]>>B67_y[countB67];
                        ++countB67;
						 clear(c,numint);
						 break;
				case 68: control>>B68_val[countB68]>>B68_dist[countB68]>>B68_b[countB68]>>B68_x[countB68]>>B68_y[countB68];
                        ++countB68;
						 clear(c,numint);
						 break;
				case 69: control>>B69_val[countB69]>>B69_dist[countB69]>>B69_b[countB69]>>B69_x[countB69]>>B69_y[countB69];
                        ++countB69;
						 clear(c,numint);
						 break;
				case 70: control>>B70_val[countB70]>>B70_dist[countB70]>>B70_b[countB70]>>B70_x[countB70]>>B70_y[countB70];
                        ++countB70;
						 clear(c,numint);
						 break;
				case 71: control>>B71_val[countB71]>>B71_dist[countB71]>>B71_b[countB71]>>B71_x[countB71]>>B71_y[countB71];
                        ++countB71;
						 clear(c,numint);
						 break;
				case 106: control>>B106_b[countB106]>>B106_x[countB106]>>B106_y[countB106];
                        ++countB106;
						 clear(c,numint);
						 break;
				case 107: control>>B107_xs[countB107]>>B107_xe[countB107]>>B107_ys[countB107]>>B107_ye[countB107]>>B107_d[countB107];
                        ++countB107;
						 clear(c,numint);
						 break;
                case 108: control>>B108_xs[countB108]>>B108_xe[countB108]>>B108_ys[countB108]>>B108_ye[countB108]>>B108_d[countB108];
                        ++countB108;
						 clear(c,numint);
						 break;
                case 240: control>>B240_C[countB240]>>B240_D[countB240]>>B240_xs[countB240]>>B240_xe[countB240]>>B240_ys[countB240]>>B240_ye[countB240]>>B240_zs[countB240]>>B240_ze[countB240];
                        ++countB240;
						 clear(c,numint);
						 break;
                case 270: control>>B270_xs[countB270]>>B270_xe[countB270]>>B270_ys[countB270]>>B270_ye[countB270]>>B270_zs[countB270]>>B270_ze[countB270]>>B270_n[countB270]>>B270_d50[countB270]>>B270_alpha[countB270]>>B270_beta[countB270];
                        ++countB270;
						 clear(c,numint);
						 break;
                case 274: control>>B274_xc[countB274]>>B274_yc[countB274]>>B274_zs[countB274]>>B274_ze[countB274]>>B274_r[countB274]>>B274_n[countB274]>>B274_d50[countB274]>>B274_alpha[countB274]>>B274_beta[countB274];
                        ++countB274;
						 clear(c,numint);
						 break;
                case 281: control>>B281_xs[countB281]>>B281_xe[countB281]>>B281_ys[countB281]>>B281_ye[countB281]>>B281_zs[countB281]>>B281_ze[countB281]>>B281_n[countB281]>>B281_d50[countB281]>>B281_alpha[countB281]>>B281_beta[countB281];
                        ++countB281;
						 clear(c,numint);
						 break;
                case 291: control>>B291_xs[countB291]>>B291_xe[countB291]>>B291_ys[countB291]>>B291_ye[countB291]>>B291_zs[countB291]>>B291_ze[countB291]>>B291_d[countB291]>>B291_n[countB291]>>B291_d50[countB291]>>B291_alpha[countB291]>>B291_beta[countB291];
                        ++countB291;
						 clear(c,numint);
						 break;
                case 310: control>>B310_xs[countB310]>>B310_xe[countB310]>>B310_ys[countB310]>>B310_ye[countB310]>>B310_zs[countB310]>>B310_ze[countB310]>>B310_N[countB310]>>B310_D[countB310]>>B310_Cd[countB310];
                        ++countB310;
						 clear(c,numint);
						 break;
				}
				break;
				
			case 'C': control>>numint;
				switch(numint)
				{
				case 75: control>>C75_x[countC75]>>C75_z[countC75]>>C75_a[countC75]>>C75_s[countC75]>>C75_l[countC75]>>C75_v[countC75];
						 ++countC75;
						 clear(c,numint);
						 break;
				}
				break;
				
		    case 'F': control>>numint;
				switch(numint)
				{

                case 70: control>>F70_xs[countF70]>>F70_xe[countF70]>>F70_ys[countF70]>>F70_ye[countF70]>>F70_zs[countF70]>>F70_ze[countF70];
                        ++countF70;
						 clear(c,numint);
						 break;
				case 71: control>>F71_xs[countF71]>>F71_xe[countF71]>>F71_ys[countF71]>>F71_ye[countF71]>>F71_zs[countF71]>>F71_ze[countF71];
                        ++countF71;
						 clear(c,numint);
						 break;
				case 72: control>>F72_xs[countF72]>>F72_xe[countF72]>>F72_ys[countF72]>>F72_ye[countF72]>>F72_h[countF72];
                        ++countF72;
						 clear(c,numint);
						 break;
               case 369: control>>F369_x[countF369]>>F369_z[countF369]>>F369_a[countF369]>>F369_s[countF369]>>F369_l[countF369]>>F369_v[countF369];
                        ++countF369;
						 clear(c,numint);
						 break;
				case 370: control>>F370_xs[countF370]>>F370_xe[countF370]>>F370_ys[countF370]>>F370_ye[countF370]>>F370_zs[countF370]>>F370_ze[countF370];
                        ++countF370;
						 clear(c,numint);
						 break;
				case 371: control>>F371_xs[countF371]>>F371_xe[countF371]>>F371_ys[countF371]>>F371_ye[countF371]>>F371_zs[countF371]>>F371_ze[countF371];
                        ++countF371;
						 clear(c,numint);
						 break;
               case 374: control>>F374_xc[countF374]>>F374_zc[countF374]>>F374_r[countF374];
                        ++countF374;
						 clear(c,numint);
						 break;
               case 375: control>>F375_xc[countF375]>>F375_zc[countF375]>>F375_r[countF375];
                        ++countF375;
						 clear(c,numint);
						 break;
               case 378: control>>F378_xc[countF378]>>F378_yc[countF378]>>F378_zc[countF378]>>F378_r[countF378];
                        ++countF378;
						 clear(c,numint);
						 break;
               case 379: control>>F379_xc[countF379]>>F379_yc[countF379]>>F379_zc[countF379]>>F379_r[countF379];
                        ++countF379;
						 clear(c,numint);
						 break;
				case 390: control>>F390_xs[countF390]>>F390_xe[countF390]>>F390_ys[countF390]>>F390_ye[countF390]>>F390_zs[countF390]>>F390_ze[countF390];
                        ++countF390;
						 clear(c,numint);
						 break;
				case 391: control>>F391_xs[countF391]>>F391_xe[countF391]>>F391_ys[countF391]>>F391_ye[countF391]>>F391_zs[countF391]>>F391_ze[countF391];
                        ++countF391;
						 clear(c,numint);
						 break;
               case 394: control>>F394_xc[countF394]>>F394_zc[countF394]>>F394_r[countF394];
                        ++countF394;
						 clear(c,numint);
						 break;
               case 395: control>>F395_xc[countF395]>>F395_zc[countF395]>>F395_r[countF395];
                        ++countF395;
						 clear(c,numint);
						 break;
               case 398: control>>F398_xc[countF398]>>F398_yc[countF398]>>F398_zc[countF398]>>F398_r[countF398];
                        ++countF398;
						 clear(c,numint);
						 break;
               case 399: control>>F399_xc[countF399]>>F399_yc[countF399]>>F399_zc[countF399]>>F399_r[countF399];
                        ++countF399;
						 clear(c,numint);
						 break;
				}
				break;

            case 'G': control>>numint;
				switch(numint)
				{

                case 60: control>>G60_xs[countG60]>>G60_xe[countG60]>>G60_ys[countG60]>>G60_ye[countG60]>>G60_zs[countG60]>>G60_ze[countG60];
                        ++countG60;
						 clear(c,numint);
						 break;
                case 61: control>>G61_xs[countG61]>>G61_xe[countG61]>>G61_ys[countG61]>>G61_ye[countG61]>>G61_zs[countG61]>>G61_ze[countG61];
                        ++countG61;
						 clear(c,numint);
						 break;
				case 81: control>>G81_xs[countG81]>>G81_xe[countG81]>>G81_ys[countG81]>>G81_ye[countG81]>>G81_zs[countG81]>>G81_ze[countG81];
                        ++countG81;
						 clear(c,numint);
						 break;
				case 95: control>>G95_xs[countG95]>>G95_xe[countG95]>>G95_ys[countG95]>>G95_ye[countG95]>>G95_zs[countG95]>>G95_ze[countG95];
                        ++countG95;
						 clear(c,numint);
						 break;
					
				}
				break;


		    case 'P': control>>numint;
				switch(numint)
				{
				 case 35: control>>P35_ts[countP35]>>P35_te[countP35]>>P35_dt[countP35];
                        ++countP35;
						 clear(c,numint);
						 break;
                case 50: control>>P50_x[countP50]>>P50_y[countP50];
                        ++countP50;
						 clear(c,numint);
						 break;
				case 51: control>>P51_x[countP51]>>P51_y[countP51];
                        ++countP51;
						 clear(c,numint);
						 break;
                case 52: control>>P52_y[countP52];
                        ++countP52;
						 clear(c,numint);
						 break;
				case 56: control>>P56_x[countP56];
                        ++countP56;
						 clear(c,numint);
						 break;
				case 61: control>>P61_x[countP61]>>P61_y[countP61]>>P61_z[countP61];
                        ++countP61;
						 clear(c,numint);
						 break;
				case 62: control>>P62_xs[countP62]>>P62_xe[countP62]>>P62_ys[countP62]>>P62_ye[countP62]>>P62_zs[countP62]>>P62_ze[countP62];
                        ++countP62;
						 clear(c,numint);
						 break;
				case 67: control>>P67_x[countP67];
                        ++countP67;
						 clear(c,numint);
						 break;
				case 81: control>>P81_xs[countP81]>>P81_xe[countP81]>>P81_ys[countP81]>>P81_ye[countP81]>>P81_zs[countP81]>>P81_ze[countP81];
                        ++countP81;
						 clear(c,numint);
						 break;
				case 85: control>>P85_xs[countP85]>>P85_xe[countP85]>>P85_ys[countP85]>>P85_ye[countP85]>>P85_zs[countP85]>>P85_ze[countP85];
                        ++countP85;
						 clear(c,numint);
						 break;
				case 121: control>>P121_x[countP121]>>P121_y[countP121];
                        ++countP121;
						 clear(c,numint);
						 break;
				case 123: control>>P123_y[countP123];
                        ++countP123;
						 clear(c,numint);
						 break;
				case 124: control>>P124_x[countP124];
                        ++countP124;
						 clear(c,numint);
						 break;
				case 125: control>>P125_x[countP125]>>P125_y[countP125];
                        ++countP125;
						 clear(c,numint);
						 break;
               case 230: control>>P230_x[countP230];
                        ++countP230;
						 clear(c,numint);
						 break;
               case 240: control>>P240_x[countP240];
                        ++countP240;
						 clear(c,numint);
						 break;
				case 351: control>>P351_x[countP351]>>P351_y[countP351];
                        ++countP351;
						 clear(c,numint);
						 break;
				case 352: control>>P352_x[countP352]>>P352_y[countP352];
                        ++countP352;
						 clear(c,numint);
						 break;
				}
				break;
                
            case 'S': control>>numint;
				switch(numint)
				{
				case 73: control>>S73_val[countS73]>>S73_dist[countS73]>>S73_b[countS73]>>S73_x[countS73]>>S73_y[countS73];
                        ++countS73;
						 clear(c,numint);
						 break;
				}
				break;
				
				
			case 'X': control>>numint;
				switch(numint)
				{

                case 110: control>>X110_xs[countX110]>>X110_xe[countX110]>>X110_ys[countX110]>>X110_ye[countX110]>>X110_zs[countX110]>>X110_ze[countX110];
                        ++countX110;
						 clear(c,numint);
						 break;
                case 163: control>>X163_x1[countX163]>>X163_y1[countX163]>>X163_z1[countX163]>>X163_x2[countX163]>>X163_y2[countX163]>>X163_z2[countX163]
                                 >>X163_x3[countX163]>>X163_y3[countX163]>>X163_z3[countX163]>>X163_x4[countX163]>>X163_y4[countX163]>>X163_z4[countX163]
                                 >>X163_x5[countX163]>>X163_y5[countX163]>>X163_z5[countX163]>>X163_x6[countX163]>>X163_y6[countX163]>>X163_z6[countX163];
                        ++countX163;
						 clear(c,numint);
						 break;
                case 164: control>>X164_x1[countX164]>>X164_y1[countX164]>>X164_z1[countX164]>>X164_x2[countX164]>>X164_y2[countX164]>>X164_z2[countX164]
                                 >>X164_x3[countX164]>>X164_y3[countX164]>>X164_z3[countX164]>>X164_x4[countX164]>>X164_y4[countX164]>>X164_z4[countX164]
                                 >>X164_x5[countX164]>>X164_y5[countX164]>>X164_z5[countX164]>>X164_x6[countX164]>>X164_y6[countX164]>>X164_z6[countX164]
                                 >>X164_x7[countX164]>>X164_y7[countX164]>>X164_z7[countX164]>>X164_x8[countX164]>>X164_y8[countX164]>>X164_z8[countX164];
                        ++countX164;
						 clear(c,numint);
						 break;
						 
				case 311: control>>X311_xs[countX311]>>X311_xe[countX311]>>X311_ys[countX311]>>X311_ye[countX311]>>X311_zs[countX311]>>X311_ze[countX311]
								>>X311_w[countX311]>>X311_rho_c[countX311]>>X311_EA[countX311]>>X311_d[countX311]>>X311_l[countX311]>>X311_H[countX311]
								>>X311_P[countX311]>>X311_facT[countX311];
                        ++countX311;
						 clear(c,numint);
						 break;		 
				}
				break;
		}
	}

	control.close();
}
