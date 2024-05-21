#include <math.h>
#include "header.h"

int Exec(int addr) {
  byte cmd;
  int  byt; 
  int  reg;
  int  adr;
  int  flag;
  int  i;
  int  j;
  byte b2;
  double d;
  double x;
  double y;
  char n[32];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  cmd = ram[adr--];
  if (cmd == 0x54 && FlagSet(22)) cmd = 0x1c;
  if (debug) printf("Exec: %02x %02x\n",cmd,ram[adr]);
  if ((cmd < 0x10 || cmd > 0x1c) && FlagSet(22)) {
    StoreNumber(Normalize(RecallNumber(REG_X)), REG_X);
    ClearFlag(22);
    }
  switch (cmd) {
    case 0x00:                                             // NULL
         break;
    case 0x01:                                             // LBL 00
         break;
    case 0x02:                                             // LBL 01
         break;
    case 0x03:                                             // LBL 02
         break;
    case 0x04:                                             // LBL 03
         break;
    case 0x05:                                             // LBL 04
         break;
    case 0x06:                                             // LBL 05
         break;
    case 0x07:                                             // LBL 06
         break;
    case 0x08:                                             // LBL 07
         break;
    case 0x09:                                             // LBL 08
         break;
    case 0x0a:                                             // LBL 09
         break;
    case 0x0b:                                             // LBL 10
         break;
    case 0x0c:                                             // LBL 11
         break;
    case 0x0d:                                             // LBL 12
         break;
    case 0x0e:                                             // LBL 13
         break;
    case 0x0f:                                             // LBL 14
         break;

    case 0x10:                                             // 0
         AddNumber(0);
         break;
    case 0x11:                                             // 1
         AddNumber(1);
         break;
    case 0x12:                                             // 2
         AddNumber(2);
         break;
    case 0x13:                                             // 3
         AddNumber(3);
         break;
    case 0x14:                                             // 4
         AddNumber(4);
         break;
    case 0x15:                                             // 5
         AddNumber(5);
         break;
    case 0x16:                                             // 6
         AddNumber(6);
         break;
    case 0x17:                                             // 7
         AddNumber(7);
         break;
    case 0x18:                                             // 8
         AddNumber(8);
         break;
    case 0x19:                                             // 9
         AddNumber(9);
         break;
    case 0x1a:                                             // .
         AddNumber(10);
         break;
    case 0x1b:                                             // EEX
         AddNumber(11);
         break;
    case 0x1c:                                             // CHS
         AddNumber(12);
         break;

    case 0x20:                                             // RCL 00
         a = Rcl(0);
         StoreNumber(a, REG_X);
         break;
    case 0x21:                                             // RCL 01
         a = Rcl(1);
         StoreNumber(a, REG_X);
         break;
    case 0x22:                                             // RCL 02
         a = Rcl(2);
         StoreNumber(a, REG_X);
         break;
    case 0x23:                                             // RCL 03
         a = Rcl(3);
         StoreNumber(a, REG_X);
         break;
    case 0x24:                                             // RCL 04
         a = Rcl(4);
         StoreNumber(a, REG_X);
         break;
    case 0x25:                                             // RCL 05
         a = Rcl(5);
         StoreNumber(a, REG_X);
         break;
    case 0x26:                                             // RCL 06
         a = Rcl(6);
         StoreNumber(a, REG_X);
         break;
    case 0x27:                                             // RCL 07
         a = Rcl(7);
         StoreNumber(a, REG_X);
         break;
    case 0x28:                                             // RCL 08
         a = Rcl(8);
         StoreNumber(a, REG_X);
         break;
    case 0x29:                                             // RCL 09
         a = Rcl(9);
         StoreNumber(a, REG_X);
         break;
    case 0x2a:                                             // RCL 10
         a = Rcl(10);
         StoreNumber(a, REG_X);
         break;
    case 0x2b:                                             // RCL 11
         a = Rcl(11);
         StoreNumber(a, REG_X);
         break;
    case 0x2c:                                             // RCL 12
         a = Rcl(12);
         StoreNumber(a, REG_X);
         break;
    case 0x2d:                                             // RCL 13
         a = Rcl(13);
         StoreNumber(a, REG_X);
         break;
    case 0x2e:                                             // RCL 14
         a = Rcl(14);
         StoreNumber(a, REG_X);
         break;
    case 0x2f:                                             // RCL 15
         a = Rcl(15);
         StoreNumber(a, REG_X);
         break;

    case 0x30:                                             // STO 00
         a = RecallNumber(REG_X);
         Sto(a, 0);
         break;
    case 0x31:                                             // STO 01
         a = RecallNumber(REG_X);
         Sto(a, 1);
         break;
    case 0x32:                                             // STO 02
         a = RecallNumber(REG_X);
         Sto(a, 2);
         break;
    case 0x33:                                             // STO 03
         a = RecallNumber(REG_X);
         Sto(a, 3);
         break;
    case 0x34:                                             // STO 04
         a = RecallNumber(REG_X);
         Sto(a, 4);
         break;
    case 0x35:                                             // STO 05
         a = RecallNumber(REG_X);
         Sto(a, 5);
         break;
    case 0x36:                                             // STO 06
         a = RecallNumber(REG_X);
         Sto(a, 6);
         break;
    case 0x37:                                             // STO 07
         a = RecallNumber(REG_X);
         Sto(a, 7);
         break;
    case 0x38:                                             // STO 08
         a = RecallNumber(REG_X);
         Sto(a, 8);
         break;
    case 0x39:                                             // STO 09
         a = RecallNumber(REG_X);
         Sto(a, 9);
         break;
    case 0x3a:                                             // STO 10
         a = RecallNumber(REG_X);
         Sto(a, 10);
         break;
    case 0x3b:                                             // STO 11
         a = RecallNumber(REG_X);
         Sto(a, 11);
         break;
    case 0x3c:                                             // STO 12
         a = RecallNumber(REG_X);
         Sto(a, 12);
         break;
    case 0x3d:                                             // STO 13
         a = RecallNumber(REG_X);
         Sto(a, 13);
         break;
    case 0x3e:                                             // STO 14
         a = RecallNumber(REG_X);
         Sto(a, 14);
         break;
    case 0x3f:                                             // STO 15
         a = RecallNumber(REG_X);
         Sto(a, 15);
         break;

    case 0x40:                                             // +
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         c = Add(a,b);
         StoreNumber(c,REG_X);
         StoreNumber(a,REG_L);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x41:                                             // -
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         c = Sub(b,a);
         StoreNumber(c,REG_X);
         StoreNumber(a,REG_L);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x42:                                             // *
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         c = Mul(a,b);
         StoreNumber(c,REG_X);
         StoreNumber(a,REG_L);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x43:                                             // /
         b = RecallNumber(REG_X);
         a = RecallNumber(REG_Y);
         c = Div(a,b);
         StoreNumber(c,REG_X);
         StoreNumber(b,REG_L);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x44:                                             // X<Y?
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         c = Sub(a, b);
         if (reg < 0x0c0) {
           if (c.sign != 0) Message("YES");
             else Message("NO");
           }
         else {
           if (c.sign == 0) adr -= isize(adr);
           }
         break;
    case 0x45:                                             // X>Y?
         b = RecallNumber(REG_X);
         a = RecallNumber(REG_Y);
         c = Sub(a, b);
         if (reg < 0x0c0) {
           if (c.sign != 0) Message("YES");
             else Message("NO");
           }
         else {
           if (c.sign == 0) adr -= isize(adr);
           }
         break;
    case 0x46:                                             // X<=Y?
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         c = Sub(a, b);
         flag = 0;
         if (c.sign != 0) flag = -1;
         if (IsZero(c)) flag = -1;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x47:                                             // E+
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         EPlus();
         break;
    case 0x48:                                             // E-
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         EMinus();
         break;
    case 0x49:                                             // HMS+
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         StoreNumber(a, REG_L);
         a = HmsPlus(a, b);
         StoreNumber(a, REG_X);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x4a:                                             // HMS-
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         StoreNumber(a, REG_L);
         a = HmsMinus(a, b);
         StoreNumber(a, REG_X);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x4b:                                             // MOD
         b = RecallNumber(REG_X);
         a = RecallNumber(REG_Y);
         c = Mod(a,b);
         StoreNumber(c,REG_X);
         StoreNumber(b,REG_L);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x4c:                                             // %
         a = RecallNumber(REG_Y);
         b = RecallNumber(REG_X);
         StoreNumber(b, REG_L);
         i = b.exponent[0] * 10 + b.exponent[1];
         if (b.esign) i = -i;
         i -= 2;
         b.esign = (i < 0) ? 9 : 0;
         if (i < 0) i = -i;
         b.exponent[0] = i / 10;
         b.exponent[1] = i % 10;
         c = Mul(a, b);
         StoreNumber(c,REG_X);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x4d:                                             // %ch
         a = RecallNumber(REG_Y);
         b = RecallNumber(REG_X);
         StoreNumber(b, REG_L);
         c = Sub(b, a);
         i = c.exponent[0] * 10 + c.exponent[1];
         if (c.esign) i = -i;
         i += 2;
         c.esign = (i < 0) ? 9 : 0;
         if (i < 0) i = -i;
         c.exponent[0] = i / 10;
         c.exponent[1] = i % 10;
         c = Div(c, a);
         StoreNumber(c,REG_X);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x4e:                                             // P-R
         a = RecallNumber(REG_X);
         NtoA(a, n);
         x = atof(n);
         b = RecallNumber(REG_Y);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) b = Mul(b, DTOR);
         else if (FlagSet(42)) b = Mul(b, GTOR);
         NtoA(b, n);
         y = atof(n);
         d = cos(y) * x;
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         SetX(a, 1, 0);
         d = sin(y) * x;
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_Y);
         break;
    case 0x4f:                                             // R-P
         a = RecallNumber(REG_X);
         NtoA(a, n);
         x = atof(n);
         b = RecallNumber(REG_Y);
         NtoA(b, n);
         y = atof(n);
         d = sqrt(x*x+y*y);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         SetX(a, 1, 0);
         d = asin(y/d);
         if (x < 0 && y >= 0) d = M_PI - d;
         if (x < 0 && y < 0) d = -(M_PI + d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, REG_Y);
         break;

    case 0x50:                                             // LN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = log(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x51:                                             // X^2
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Mul(a,a);
         StoreNumber(a, REG_X);
         break;
    case 0x52:                                             // SQRT
         a = RecallNumber(REG_X);
         NtoA(a, n);
         d = atof(n);
         d = sqrt(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         SetX(a, 1, 0);
         break;
    case 0x53:                                             // Y^X
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         x = atof(n);
         a = RecallNumber(REG_Y);
         NtoA(a, n);
         y = atof(n);
         d = pow(y,x);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         a = RecallNumber(REG_Z);
         StoreNumber(a,REG_Y);
         a = RecallNumber(REG_T);
         StoreNumber(a,REG_Z);
         break;
    case 0x54:                                             // CHS
         a = RecallNumber(REG_X);
         a.sign = (a.sign == 0) ? 9 : 0;
         SetX(a, 0, 0);
         break;
    case 0x55:                                             // E^X
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = pow(M_E,d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x56:                                             // LOG
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = log10(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x57:                                             // 10^X
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = pow(10,d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x58:                                             // E^X-1
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = pow(M_E,d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x59:                                             // SIN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         NtoA(a, n);
         d = atof(n);
         d = sin(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x5a:                                             // COS
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         NtoA(a, n);
         d = atof(n);
         d = cos(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x5b:                                             // TAN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         NtoA(a, n);
         d = atof(n);
         d = tan(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x5c:                                             // ASIN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = asin(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, REG_X);
         break;
    case 0x5d:                                             // ACOS
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = acos(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, REG_X);
         break;
    case 0x5e:                                             // ATAN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = atan(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, REG_X);
         break;
    case 0x5f:                                             // DEC
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Dec(a);
         StoreNumber(a, REG_X);
         break;

    case 0x60:                                             // 1/X
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Div(ONE,a);
         StoreNumber(a, REG_X);
         break;
    case 0x61:                                             // ABS
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a.sign = 0;
         StoreNumber(a, REG_X);
         break;
    case 0x62:                                             // FACT
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Fact(a);
         StoreNumber(a, REG_X);
         break;
    case 0x63:                                             // X<>0?
         a = RecallNumber(REG_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x64:                                             // X>0?
         a = RecallNumber(REG_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (a.sign) flag = 0;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x65:                                             // LN1+X
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         NtoA(a, n);
         d = atof(n);
         d = log1p(d);
         sprintf(n,"%.12e",d);
         a = AtoN(n);
         StoreNumber(a, REG_X);
         break;
    case 0x66:                                             // X<0?
         a = RecallNumber(REG_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (a.sign == 0) flag = 0;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x67:                                             // X=0?
         a = RecallNumber(REG_X);
         flag = -1;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = 0;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x68:                                             // INT
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Integer(a);
         StoreNumber(a, REG_X);
         break;
    case 0x69:                                             // FRC
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Fractional(a);
         StoreNumber(a, REG_X);
         break;
    case 0x6a:                                             // D-R
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Mul(a, DTOR);
         StoreNumber(a, REG_X);
         break;
    case 0x6b:                                             // R-D
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Mul(a, RTOD);
         StoreNumber(a, REG_X);
         break;
    case 0x6c:                                             // HMS
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Hms(a);
         StoreNumber(a, REG_X);
         break;
    case 0x6d:                                             // HR
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Hr(a);
         StoreNumber(a, REG_X);
         break;
    case 0x6e:                                             // RND
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         Rnd();
         break;
    case 0x6f:                                             // OCT
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         a = Oct(a);
         StoreNumber(a, REG_X);
         break;

    case 0x70:                                             // CLE
         Cle();
         break;
    case 0x71:                                             // X<>Y
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         StoreNumber(b, REG_X);
         StoreNumber(a, REG_Y);
         break;
    case 0x72:                                             // PI
         StoreNumber(PI, REG_X);
         break;
    case 0x73:                                             // CLST
         StoreNumber(ZERO, REG_X);
         StoreNumber(ZERO, REG_Y);
         StoreNumber(ZERO, REG_Z);
         StoreNumber(ZERO, REG_T);
         break;
    case 0x74:                                             // R^
         a = RecallNumber(REG_T);
         b = RecallNumber(REG_Z);
         StoreNumber(b, REG_T);
         b = RecallNumber(REG_Y);
         StoreNumber(b, REG_Z);
         b = RecallNumber(REG_X);
         StoreNumber(b, REG_Y);
         StoreNumber(a, REG_X);
         break;
    case 0x75:                                             // RDN
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         StoreNumber(b, REG_X);
         b = RecallNumber(REG_Z);
         StoreNumber(b, REG_Y);
         b = RecallNumber(REG_T);
         StoreNumber(b, REG_Z);
         StoreNumber(a, REG_T);
         break;
    case 0x76:                                             // LASTX
         a = RecallNumber(REG_L);
         StoreNumber(a, REG_X);
         break;
    case 0x77:                                             // CLX
         StoreNumber(ZERO,REG_X);
         break;
    case 0x78:                                             // X=Y?
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         flag = -1;
         if (a.sign != b.sign) flag = 0;
         if (a.esign != b.esign) flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != b.mantissa[i]) flag = 0;
         for (i=0; i<2; i++)
           if (a.exponent[i] != b.exponent[i]) flag = 0;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x79:                                             // X<>Y?
         a = RecallNumber(REG_X);
         b = RecallNumber(REG_Y);
         flag = 0;
         if (a.sign != b.sign) flag = -1;
         if (a.esign != b.esign) flag = -1;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != b.mantissa[i]) flag = -1;
         for (i=0; i<2; i++)
           if (a.exponent[i] != b.exponent[i]) flag = -1;
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x7a:                                             // SIGN
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_L);
         if (a.mantissa[0] == 0 && a.mantissa[1] == 0 &&
             a.mantissa[2] == 0 && a.mantissa[3] == 0 &&
             a.mantissa[4] == 0 && a.mantissa[5] == 0 &&
             a.mantissa[6] == 0 && a.mantissa[7] == 0 &&
             a.mantissa[8] == 0 && a.mantissa[9] == 0)
            StoreNumber(ONE, REG_X);
         else if (a.sign == 0) StoreNumber(ONE, REG_X);
         else if (a.sign != 0) StoreNumber(NEGONE, REG_X);
         break;
    case 0x7b:                                             // X<=0?
         a = RecallNumber(REG_X);
         if (a.sign) flag = -1;
         else {
           flag = -1;
           for (i=0; i<10; i++)
             if (a.mantissa[i] != 0) flag = 0;
           }
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0x7c:                                             // MEAN
         Mean();
         break;
    case 0x7d:                                             // SDEV
         Sdev();
         break;
    case 0x7e:                                             // AVIEW
         Aview();
         SetFlag(50);
         break;
    case 0x7f:                                             // CLD
         ClearFlag(50);
         break;

    case 0x80:                                             // DEG
         ClearFlag(42);
         ClearFlag(43);
         break;
    case 0x81:                                             // RAD
         ClearFlag(42);
         SetFlag(43);
         break;
    case 0x82:                                             // GRAD
         ClearFlag(43);
         SetFlag(42);
         break;
    case 0x83:                                             // ENTER^
         a = RecallNumber(REG_Z);
         StoreNumber(a, REG_T);
         a = RecallNumber(REG_Y);
         StoreNumber(a, REG_Z);
         a = RecallNumber(REG_X);
         StoreNumber(a, REG_Y);
         break;
    case 0x84:                                             // STOP
         running = 0;
         break;
    case 0x85:                                             // RTN
         Rtn();
         break;
    case 0x86:                                             // BEEP
         break;
    case 0x87:                                             // CLA
         for (i=REG_M*7; i<REG_P*7+3; i++)
           ram[i] = 0;
         break;
    case 0x88:                                             // ASHF
         i = REG_P*7 + 2;
         while (i > REG_M*7 && ram[i] == 0) i--;
         for (j=0; j<6; j++)
           if (i >= REG_M*7) ram[i--] = 0; 
         break;
    case 0x8a:                                             // CLRG
         Clrg();
         break;
    case 0x8b:                                             // AOFF
         ClearFlag(48);
         break;
    case 0x8c:                                             // AON
         SetFlag(48);
         break;
    case 0x8d:                                             // OFF
         on = 0;
         break;
    case 0x8e:                                             // PROMPT
         Aview();
         running = 0;
         break;
        
    case 0x90:                                             // RCL
         b2 = ram[adr--];
         a = Rcl(b2);
         StoreNumber(a, REG_X);
         break;
    case 0x91:                                             // STO
         a = RecallNumber(REG_X);
         b2 = ram[adr--];
         Sto(a, b2);
         break;
    case 0x92:                                             // ST+
         b2 = ram[adr--];
         a = RecallNumber(REG_X);
         b = Rcl(b2);
         a = Add(a,b);
         Sto(a, b2);
         break;
    case 0x93:                                             // ST-
         b2 = ram[adr--];
         b = RecallNumber(REG_X);
         a = Rcl(b2);
         a = Sub(a,b);
         Sto(a, b2);
         break;
    case 0x94:                                             // ST*
         b2 = ram[adr--];
         a = RecallNumber(REG_X);
         b = Rcl(b2);
         a = Mul(a,b);
         Sto(a, b2);
         break;
    case 0x95:                                             // ST/
         b2 = ram[adr--];
         b = RecallNumber(REG_X);
         a = Rcl(b2);
         a = Div(a,b);
         Sto(a, b2);
         break;
    case 0x96:                                             // ISG
         i = Isg(ram[adr--]);
         if (reg >= 0x0c0) {
           if (i != 0) adr -= isize(adr);
           }
         break;
    case 0x97:                                             // DSE
         i = Dse(ram[adr--]);
         if (reg >= 0x0c0) {
           if (i != 0) adr -= isize(adr);
           }
         break;
    case 0x98:                                             // VIEW
         View(ram[adr--]);
         break;
    case 0x99:                                             // EREG
         EReg(ram[adr--]);
         break;
    case 0x9a:                                             // ASTO
         Asto(ram[adr--]);
         break;
    case 0x9b:                                             // ARCL
         Arcl(ram[adr--]);
         break;
    case 0x9c:                                             // FIX
         Fix(ram[adr--]);
         break;
    case 0x9d:                                             // SCI
         Sci(ram[adr--]);
         break;
    case 0x9e:                                             // ENG
         Eng(ram[adr--]);
         break;
    case 0x9f:                                             // TONE
         Tone(ram[adr--]);
         break;
   
    case 0xa8:                                             // SF
         Sf(ram[adr--]);
         break;
    case 0xa9:                                             // CF
         Cf(ram[adr--]);
         break;
    case 0xaa:                                             // FS?C
         flag = FsQc(ram[adr--]);
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0xab:                                             // FC?C
         flag = FsQc(ram[adr--]);
         if (reg < 0x0c0) {
           if (flag) Message("NO");
             else Message("YES");
           }
         else {
           if (flag != 0) adr -= isize(adr);
           }
         break;
    case 0xac:                                             // FS?
         flag = Fs(ram[adr--]);
         if (reg < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) adr -= isize(adr);
           }
         break;
    case 0xad:                                             // FC?
         flag = Fs(ram[adr--]);
         if (reg < 0x0c0) {
           if (flag) Message("NO");
             else Message("YES");
           }
         else {
           if (flag != 0) adr -= isize(adr);
           }
         break;

    case 0xce:                                             // X<>
         b2 = ram[adr--];
         a = RecallNumber(REG_X);
         b = Rcl(b2);
         Sto(a, b2);
         StoreNumber(b, REG_X);
         break;
    case 0xcf:                                             // LBL
         adr--;
         break;

    case 0xf0:                                             // TEXT 0
         for (i=REG_M*7; i<=REG_P*7+2; i++)
           ram[i] = 0;
         break;
    case 0xf1:                                             // TEXT 1
    case 0xf2:                                             // TEXT 2
    case 0xf3:                                             // TEXT 3
    case 0xf4:                                             // TEXT 4
    case 0xf5:                                             // TEXT 5
    case 0xf6:                                             // TEXT 6
    case 0xf7:                                             // TEXT 7
    case 0xf8:                                             // TEXT 8
    case 0xf9:                                             // TEXT 9
    case 0xfa:                                             // TEXT 10
    case 0xfb:                                             // TEXT 11
    case 0xfc:                                             // TEXT 12
    case 0xfd:                                             // TEXT 13
    case 0xfe:                                             // TEXT 14
    case 0xff:                                             // TEXT 15
         if (ram[adr] != 0x7f) {
           for (i=REG_M*7; i<=REG_P*7+2; i++)
             ram[i] = 0;
           }
         for (i=0; i<(cmd & 0x0f); i++) {
           for (j=REG_P*7+2; j>REG_M*7; j--)
             ram[j] = ram[j-1];
           ram[REG_M*7] = ram[adr--];
           }
         break;

    }
  reg = adr / 7;
  byt = adr % 7;
  addr = (byt << 12) | reg;
//printf("Return = %x\n",addr);
  return addr;
  }

