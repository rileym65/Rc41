#include <math.h>
#include "header.h"

int Exec(int addr) {
  byte cmd;
  int  byt; 
  int  flag;
  int  i;
  int  j;
  int  oaddr;
  char buffer[64];
  byte b2;
  double d;
  double x;
  double y;
  NUMBER nm;
  char n[32];
  oaddr = addr;
  cmd = 0;
  errFlag = 0;
  while (cmd == 0) cmd = ram[addr--];
  if (running == 0 && cmd == 0x54 && FlagSet(22)) cmd = 0x1c;
  if (debug) {
    ProgramList(1, addr+1, buffer);
    printf("-->%s\n",buffer);
    }
  if (running == 0) {
    if ((cmd < 0x10 || cmd > 0x1c) && FlagSet(22)) {
      ClearFlag(22);
      nm = RecallNumber(R_X);
      i = (nm.exponent[0] * 10) + nm.exponent[1];
      if (nm.esign) i = -i;
      ex += i;
      nm.esign = (ex < 0) ? 9 : 0;
      if (ex < 0) ex = -ex;
      nm.exponent[0] = ex / 10;
      nm.exponent[1] = ex % 10;
      StoreNumber(nm, R_X);
      ram[PENDING] = 'E';
      }
    ram[PENDING] =  (FlagSet(22) == 0) ? 'E' : 'D';
    }
  else ram[PENDING] = 'E';
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
    case 0x11:                                             // 1
    case 0x12:                                             // 2
    case 0x13:                                             // 3
    case 0x14:                                             // 4
    case 0x15:                                             // 5
    case 0x16:                                             // 6
    case 0x17:                                             // 7
    case 0x18:                                             // 8
    case 0x19:                                             // 9
    case 0x1a:                                             // .
    case 0x1b:                                             // EEX
    case 0x1c:                                             // CHS
         if (running) {
           addr = ExecNumber(addr+1);
           }
         else {
           AddNumber(cmd - 0x10);
           }
         break;
    case 0x1d:                                             // GTO"
         addr = GtoAlpha(addr);
         addr--;
         break;
    case 0x1e:                                             // XEQ"
         addr = GtoAlpha(addr);
         if (addr != 0) {
           Push((oaddr)-isize(oaddr-1));
           }
         break;
         

    case 0x20:                                             // RCL 00
         a = Rcl(0);
         StoreNumber(a, R_X);
         break;
    case 0x21:                                             // RCL 01
         a = Rcl(1);
         StoreNumber(a, R_X);
         break;
    case 0x22:                                             // RCL 02
         a = Rcl(2);
         StoreNumber(a, R_X);
         break;
    case 0x23:                                             // RCL 03
         a = Rcl(3);
         StoreNumber(a, R_X);
         break;
    case 0x24:                                             // RCL 04
         a = Rcl(4);
         StoreNumber(a, R_X);
         break;
    case 0x25:                                             // RCL 05
         a = Rcl(5);
         StoreNumber(a, R_X);
         break;
    case 0x26:                                             // RCL 06
         a = Rcl(6);
         StoreNumber(a, R_X);
         break;
    case 0x27:                                             // RCL 07
         a = Rcl(7);
         StoreNumber(a, R_X);
         break;
    case 0x28:                                             // RCL 08
         a = Rcl(8);
         StoreNumber(a, R_X);
         break;
    case 0x29:                                             // RCL 09
         a = Rcl(9);
         StoreNumber(a, R_X);
         break;
    case 0x2a:                                             // RCL 10
         a = Rcl(10);
         StoreNumber(a, R_X);
         break;
    case 0x2b:                                             // RCL 11
         a = Rcl(11);
         StoreNumber(a, R_X);
         break;
    case 0x2c:                                             // RCL 12
         a = Rcl(12);
         StoreNumber(a, R_X);
         break;
    case 0x2d:                                             // RCL 13
         a = Rcl(13);
         StoreNumber(a, R_X);
         break;
    case 0x2e:                                             // RCL 14
         a = Rcl(14);
         StoreNumber(a, R_X);
         break;
    case 0x2f:                                             // RCL 15
         a = Rcl(15);
         StoreNumber(a, R_X);
         break;

    case 0x30:                                             // STO 00
         a = RecallNumber(R_X);
         Sto(a, 0);
         break;
    case 0x31:                                             // STO 01
         a = RecallNumber(R_X);
         Sto(a, 1);
         break;
    case 0x32:                                             // STO 02
         a = RecallNumber(R_X);
         Sto(a, 2);
         break;
    case 0x33:                                             // STO 03
         a = RecallNumber(R_X);
         Sto(a, 3);
         break;
    case 0x34:                                             // STO 04
         a = RecallNumber(R_X);
         Sto(a, 4);
         break;
    case 0x35:                                             // STO 05
         a = RecallNumber(R_X);
         Sto(a, 5);
         break;
    case 0x36:                                             // STO 06
         a = RecallNumber(R_X);
         Sto(a, 6);
         break;
    case 0x37:                                             // STO 07
         a = RecallNumber(R_X);
         Sto(a, 7);
         break;
    case 0x38:                                             // STO 08
         a = RecallNumber(R_X);
         Sto(a, 8);
         break;
    case 0x39:                                             // STO 09
         a = RecallNumber(R_X);
         Sto(a, 9);
         break;
    case 0x3a:                                             // STO 10
         a = RecallNumber(R_X);
         Sto(a, 10);
         break;
    case 0x3b:                                             // STO 11
         a = RecallNumber(R_X);
         Sto(a, 11);
         break;
    case 0x3c:                                             // STO 12
         a = RecallNumber(R_X);
         Sto(a, 12);
         break;
    case 0x3d:                                             // STO 13
         a = RecallNumber(R_X);
         Sto(a, 13);
         break;
    case 0x3e:                                             // STO 14
         a = RecallNumber(R_X);
         Sto(a, 14);
         break;
    case 0x3f:                                             // STO 15
         a = RecallNumber(R_X);
         Sto(a, 15);
         break;

    case 0x40:                                             // +
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         c = Add(a,b);
         StoreNumber(c,R_X);
         StoreNumber(a,R_L);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x41:                                             // -
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         c = Sub(b,a);
         StoreNumber(c,R_X);
         StoreNumber(a,R_L);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x42:                                             // *
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         c = Mul(a,b);
         StoreNumber(c,R_X);
         StoreNumber(a,R_L);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x43:                                             // /
         ram[LIFT] = 'D';
         b = RecallNumber(R_X);
         a = RecallNumber(R_Y);
         c = Div(a,b);
         StoreNumber(c,R_X);
         StoreNumber(b,R_L);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x44:                                             // X<Y?
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         c = Sub(a, b);
         if (addr < 0x0c0) {
           if (c.sign != 0) Message("YES");
             else Message("NO");
           }
         else {
           if (c.sign == 0) addr = Skip(addr);
           }
         break;
    case 0x45:                                             // X>Y?
         b = RecallNumber(R_X);
         a = RecallNumber(R_Y);
         c = Sub(a, b);
         if (addr < 0x0c0) {
           if (c.sign != 0) Message("YES");
             else Message("NO");
           }
         else {
           if (c.sign == 0) addr = Skip(addr);
           }
         break;
    case 0x46:                                             // X<=Y?
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         c = Sub(a, b);
         flag = 0;
         if (c.sign != 0) flag = -1;
         if (IsZero(c)) flag = -1;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x47:                                             // E+
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         EPlus();
         ram[PENDING] = 'D';
         break;
    case 0x48:                                             // E-
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         EMinus();
         ram[PENDING] = 'D';
         break;
    case 0x49:                                             // HMS+
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         StoreNumber(a, R_L);
         a = HmsPlus(a, b);
         StoreNumber(a, R_X);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x4a:                                             // HMS-
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         StoreNumber(a, R_L);
         a = HmsMinus(a, b);
         StoreNumber(a, R_X);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x4b:                                             // MOD
         b = RecallNumber(R_X);
         a = RecallNumber(R_Y);
         c = Mod(a,b);
         StoreNumber(c,R_X);
         StoreNumber(b,R_L);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x4c:                                             // %
         a = RecallNumber(R_Y);
         b = RecallNumber(R_X);
         StoreNumber(b, R_L);
         i = b.exponent[0] * 10 + b.exponent[1];
         if (b.esign) i = -i;
         i -= 2;
         b.esign = (i < 0) ? 9 : 0;
         if (i < 0) i = -i;
         b.exponent[0] = i / 10;
         b.exponent[1] = i % 10;
         c = Mul(a, b);
         StoreNumber(c,R_X);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x4d:                                             // %ch
         a = RecallNumber(R_Y);
         b = RecallNumber(R_X);
         StoreNumber(b, R_L);
         c = Sub(b, a);
         i = c.exponent[0] * 10 + c.exponent[1];
         if (c.esign) i = -i;
         i += 2;
         c.esign = (i < 0) ? 9 : 0;
         if (i < 0) i = -i;
         c.exponent[0] = i / 10;
         c.exponent[1] = i % 10;
         c = Div(c, a);
         StoreNumber(c,R_X);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x4e:                                             // P-R
         a = RecallNumber(R_X);
         NtoA(a, n);
         x = atof(n);
         b = RecallNumber(R_Y);
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
         StoreNumber(a, R_Y);
         break;
    case 0x4f:                                             // R-P
         a = RecallNumber(R_X);
         NtoA(a, n);
         x = atof(n);
         b = RecallNumber(R_Y);
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
         StoreNumber(a, R_Y);
         break;

    case 0x50:                                             // LN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Ln(a);
         StoreNumber(a, R_X);
         break;
    case 0x51:                                             // X^2
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Mul(a,a);
         StoreNumber(a, R_X);
         break;
    case 0x52:                                             // SQRT
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Sqrt(a);
         StoreNumber(a, R_X);
         break;
    case 0x53:                                             // Y^X
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         b = RecallNumber(R_Y);
         a = YtoX(a, b);
         StoreNumber(a, R_X);
         a = RecallNumber(R_Z);
         StoreNumber(a,R_Y);
         a = RecallNumber(R_T);
         StoreNumber(a,R_Z);
         break;
    case 0x54:                                             // CHS
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         a.sign = (a.sign == 0) ? 9 : 0;
         SetX(a, 0, 0);
         break;
    case 0x55:                                             // E^X
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Ex(a);
         StoreNumber(a, R_X);
         break;
    case 0x56:                                             // LOG
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Ln(a);
         a = Mul(a, LOGE);
         StoreNumber(a, R_X);
         break;
    case 0x57:                                             // 10^X
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Mul(a, ILOGE);
         a = Ex(a);
         StoreNumber(a, R_X);
         break;
    case 0x58:                                             // E^X-1
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Ex(a);
         a = Sub(a, ONE);
         StoreNumber(a, R_X);
         break;
    case 0x59:                                             // SIN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         a = Sin(a);
         StoreNumber(a, R_X);
         break;
    case 0x5a:                                             // COS
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         a = Cos(a);
         StoreNumber(a, R_X);
         break;
    case 0x5b:                                             // TAN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, DTOR);
         else if (FlagSet(42)) a = Mul(a, GTOR);
         a = Tan(a);
         StoreNumber(a, R_X);
         break;
    case 0x5c:                                             // ASIN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Asin(a);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, R_X);
         break;
    case 0x5d:                                             // ACOS
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Acos(a);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, R_X);
         break;
    case 0x5e:                                             // ATAN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Atan(a);
//         NtoA(a, n);
//         d = atof(n);
//         d = atan(d);
//         sprintf(n,"%.12e",d);
//         a = AtoN(n);
         if (FlagSet(43) == 0 && FlagSet(42) == 0) a = Mul(a, RTOD);
         else if (FlagSet(42)) a = Mul(a, RTOG);
         StoreNumber(a, R_X);
         break;
    case 0x5f:                                             // DEC
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Dec(a);
         StoreNumber(a, R_X);
         break;

    case 0x60:                                             // 1/X
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Div(ONE,a);
         StoreNumber(a, R_X);
         break;
    case 0x61:                                             // ABS
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a.sign = 0;
         StoreNumber(a, R_X);
         break;
    case 0x62:                                             // FACT
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Fact(a);
         StoreNumber(a, R_X);
         break;
    case 0x63:                                             // X<>0?
         a = RecallNumber(R_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x64:                                             // X>0?
         a = RecallNumber(R_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (a.sign) flag = 0;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x65:                                             // LN1+X
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Ln1PlusX(a);
         StoreNumber(a, R_X);
         break;
    case 0x66:                                             // X<0?
         a = RecallNumber(R_X);
         flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = -1;
         if (a.sign == 0) flag = 0;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x67:                                             // X=0?
         a = RecallNumber(R_X);
         flag = -1;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != 0) flag = 0;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x68:                                             // INT
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Integer(a);
         StoreNumber(a, R_X);
         break;
    case 0x69:                                             // FRC
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Fractional(a);
         StoreNumber(a, R_X);
         break;
    case 0x6a:                                             // D-R
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Mul(a, DTOR);
         StoreNumber(a, R_X);
         break;
    case 0x6b:                                             // R-D
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Mul(a, RTOD);
         StoreNumber(a, R_X);
         break;
    case 0x6c:                                             // HMS
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Hms(a);
         StoreNumber(a, R_X);
         break;
    case 0x6d:                                             // HR
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Hr(a);
         StoreNumber(a, R_X);
         break;
    case 0x6e:                                             // RND
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         Rnd();
         break;
    case 0x6f:                                             // OCT
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         a = Oct(a);
         StoreNumber(a, R_X);
         break;

    case 0x70:                                             // CLE
         Cle();
         break;
    case 0x71:                                             // X<>Y
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         StoreNumber(b, R_X);
         StoreNumber(a, R_Y);
         break;
    case 0x72:                                             // PI
         StoreNumber(PI, R_X);
         break;
    case 0x73:                                             // CLST
         StoreNumber(ZERO, R_X);
         StoreNumber(ZERO, R_Y);
         StoreNumber(ZERO, R_Z);
         StoreNumber(ZERO, R_T);
         break;
    case 0x74:                                             // R^
         ram[LIFT] = 'D';
         a = RecallNumber(R_T);
         b = RecallNumber(R_Z);
         StoreNumber(b, R_T);
         b = RecallNumber(R_Y);
         StoreNumber(b, R_Z);
         b = RecallNumber(R_X);
         StoreNumber(b, R_Y);
         StoreNumber(a, R_X);
         break;
    case 0x75:                                             // RDN
         ram[LIFT] = 'D';
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         StoreNumber(b, R_X);
         b = RecallNumber(R_Z);
         StoreNumber(b, R_Y);
         b = RecallNumber(R_T);
         StoreNumber(b, R_Z);
         StoreNumber(a, R_T);
         break;
    case 0x76:                                             // LASTX
         a = RecallNumber(R_L);
         StoreNumber(a, R_X);
         break;
    case 0x77:                                             // CLX
         StoreNumber(ZERO,R_X);
         ram[PENDING] = 'D';
         break;
    case 0x78:                                             // X=Y?
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         flag = -1;
         if (a.sign != b.sign) flag = 0;
         if (a.esign != b.esign) flag = 0;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != b.mantissa[i]) flag = 0;
         for (i=0; i<2; i++)
           if (a.exponent[i] != b.exponent[i]) flag = 0;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x79:                                             // X<>Y?
         a = RecallNumber(R_X);
         b = RecallNumber(R_Y);
         flag = 0;
         if (a.sign != b.sign) flag = -1;
         if (a.esign != b.esign) flag = -1;
         for (i=0; i<10; i++)
           if (a.mantissa[i] != b.mantissa[i]) flag = -1;
         for (i=0; i<2; i++)
           if (a.exponent[i] != b.exponent[i]) flag = -1;
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
           }
         break;
    case 0x7a:                                             // SIGN
         a = RecallNumber(R_X);
         StoreNumber(a, R_L);
         if (a.mantissa[0] == 0 && a.mantissa[1] == 0 &&
             a.mantissa[2] == 0 && a.mantissa[3] == 0 &&
             a.mantissa[4] == 0 && a.mantissa[5] == 0 &&
             a.mantissa[6] == 0 && a.mantissa[7] == 0 &&
             a.mantissa[8] == 0 && a.mantissa[9] == 0)
            StoreNumber(ONE, R_X);
         else if (a.sign == 0) StoreNumber(ONE, R_X);
         else if (a.sign != 0) StoreNumber(NEGONE, R_X);
         break;
    case 0x7b:                                             // X<=0?
         a = RecallNumber(R_X);
         if (a.sign) flag = -1;
         else {
           flag = -1;
           for (i=0; i<10; i++)
             if (a.mantissa[i] != 0) flag = 0;
           }
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr = Skip(addr);
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
         for (i=0; i<21; i++) ram[i] = ram[i+7];
         ram[PENDING] = 'D';
         break;
    case 0x84:                                             // STOP
         running = 0;
         ram[REG_E+1] |= 0x0f;
         ram[REG_E+0] = 0xff;
         break;
    case 0x85:                                             // RTN
         addr =Rtn(addr);
         break;
    case 0x86:                                             // BEEP
         break;
    case 0x87:                                             // CLA
         for (i=REG_M; i<REG_P+3; i++)
           ram[i] = 0;
         break;
    case 0x88:                                             // ASHF
         i = REG_P + 2;
         while (i > REG_M && ram[i] == 0) i--;
         for (j=0; j<6; j++)
           if (i >= REG_M) ram[i--] = 0; 
         break;
    case 0x8a:                                             // CLRG
         Clrg();
         break;
    case 0x8b:                                             // AOFF
         ClearFlag(48);
         break;
    case 0x8c:                                             // AON
         SetFlag(48);
         ram[PENDING] = 'N';
         break;
    case 0x8d:                                             // OFF
         on = 0;
         break;
    case 0x8e:                                             // PROMPT
         Aview();
         running = 0;
         break;
    case 0x8f:                                             // ADV
         if (FlagSet(55) && FlagSet(21)) {
           if (printPosition != 0) {
             for (i=0; i<24-strlen(buffer); i++)
               printf(" ");
             printf("%s",printBuffer);
             strcpy(printBuffer,"");
             printPosition = 0;
             }
           printf("\n");
           }
         break;
        
    case 0x90:                                             // RCL
         b2 = ram[addr--];
         a = Rcl(b2);
         StoreNumber(a, R_X);
         break;
    case 0x91:                                             // STO
         a = RecallNumber(R_X);
         b2 = ram[addr--];
         Sto(a, b2);
         break;
    case 0x92:                                             // ST+
         ram[LIFT] = 'D';
         b2 = ram[addr--];
         a = RecallNumber(R_X);
         b = Rcl(b2);
         a = Add(a,b);
         Sto(a, b2);
         break;
    case 0x93:                                             // ST-
         ram[LIFT] = 'D';
         b2 = ram[addr--];
         b = RecallNumber(R_X);
         a = Rcl(b2);
         a = Sub(a,b);
         Sto(a, b2);
         break;
    case 0x94:                                             // ST*
         ram[LIFT] = 'D';
         b2 = ram[addr--];
         a = RecallNumber(R_X);
         b = Rcl(b2);
         a = Mul(a,b);
         Sto(a, b2);
         break;
    case 0x95:                                             // ST/
         ram[LIFT] = 'D';
         b2 = ram[addr--];
         b = RecallNumber(R_X);
         a = Rcl(b2);
         a = Div(a,b);
         Sto(a, b2);
         break;
    case 0x96:                                             // ISG
         i = Isg(ram[addr--]);
         if (addr >= 0x0c0) {
           if (i != 0) addr = Skip(addr);
           }
         break;
    case 0x97:                                             // DSE
         i = Dse(ram[addr--]);
         if (addr >= 0x0c0) {
           if (i != 0) addr = Skip(addr);
           }
         break;
    case 0x98:                                             // VIEW
         View(ram[addr--]);
         break;
    case 0x99:                                             // EREG
         EReg(ram[addr--]);
         break;
    case 0x9a:                                             // ASTO
         Asto(ram[addr--]);
         break;
    case 0x9b:                                             // ARCL
         Arcl(ram[addr--]);
         break;
    case 0x9c:                                             // FIX
         Fix(ram[addr--]);
         break;
    case 0x9d:                                             // SCI
         Sci(ram[addr--]);
         break;
    case 0x9e:                                             // ENG
         Eng(ram[addr--]);
         break;
    case 0x9f:                                             // TONE
         Tone(ram[addr--]);
         break;
   
    case 0xa0:                                             // XROM
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
         b2 = ram[addr--];
         byt = ((cmd &0x0f) << 2) | ((b2 & 0xc0) >> 6);
         b2 &= 0x3f;
         if (byt == 29) Printer(b2);
         else if (byt == 28) TapeDrive(b2, addr);
         else if (byt == 30) addr = CardReader(b2, addr);
         else {
           Message("NONEXISTENT");
           Error();
           }
         break;
    case 0xa8:                                             // SF
         Sf(ram[addr--]);
         break;
    case 0xa9:                                             // CF
         Cf(ram[addr--]);
         break;
    case 0xaa:                                             // FS?C
         flag = FsQc(ram[addr--]);
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr =Skip(addr);
           }
         break;
    case 0xab:                                             // FC?C
         flag = FsQc(ram[addr--]);
         if (addr < 0x0c0) {
           if (flag) Message("NO");
             else Message("YES");
           }
         else {
           if (flag != 0) addr =Skip(addr);
           }
         break;
    case 0xac:                                             // FS?
         flag = Fs(ram[addr--]);
         if (addr < 0x0c0) {
           if (flag) Message("YES");
             else Message("NO");
           }
         else {
           if (flag == 0) addr =Skip(addr);
           }
         break;
    case 0xad:                                             // FC?
         flag = Fs(ram[addr--]);
         if (addr < 0x0c0) {
           if (flag) Message("NO");
             else Message("YES");
           }
         else {
           if (flag != 0) addr =Skip(addr);
           }
         break;
    case 0xae:                                             // GTO/XEQ IND
         b2 = ram[addr];
         addr = GtoXeqInd(addr+1);
         if (addr == 0) {
           running = 0;
           addr = oaddr;
           }
         if (addr != 0 && b2 >= 0x80) {
           Push((oaddr)-isize(oaddr-1));
           }
         break;


    case 0xb1:                                             // GTO 00
    case 0xb2:                                             // GTO 01
    case 0xb3:                                             // GTO 02
    case 0xb4:                                             // GTO 03
    case 0xb5:                                             // GTO 04
    case 0xb6:                                             // GTO 05
    case 0xb7:                                             // GTO 06
    case 0xb8:                                             // GTO 07
    case 0xb9:                                             // GTO 08
    case 0xba:                                             // GTO 09
    case 0xbb:                                             // GTO 10
    case 0xbc:                                             // GTO 11
    case 0xbd:                                             // GTO 12
    case 0xbe:                                             // GTO 13
    case 0xbf:                                             // GTO 14
         addr = Gto2(addr+1);
         break;

    case 0xc0:                                             // GLOBAL
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 0xc7:
    case 0xc8:
    case 0xc9:
    case 0xca:
    case 0xcb:
    case 0xcc:
    case 0xcd:
         addr--;
         b2 = ram[addr];
         if (b2 >= 0xf0) {                                 // Label
           addr -= (b2 & 0xf);
           addr--;
           }
         else {                                            // End
           addr =Rtn(addr);
//           running = 0;
//           addr = oaddr;
           if (addr != 0) {
printf("Return with address != 0\n");
             ram[REG_E+1] |= 0x0f;
             ram[REG_E+0] = 0xff;
             }
           else {
             ram[REG_E+1] &= 0xf0;
             ram[REG_E+0] = 0x00;
             }
           }
         break;
    case 0xce:                                             // X<>
         ram[LIFT] = 'D';
         b2 = ram[addr--];
         a = RecallNumber(R_X);
         b = Rcl(b2);
         Sto(a, b2);
         StoreNumber(b, R_X);
         break;
    case 0xcf:                                             // LBL
         addr--;
         break;

    case 0xd0:                                             // GTO
    case 0xd1:                                             // GTO
    case 0xd2:                                             // GTO
    case 0xd3:                                             // GTO
    case 0xd4:                                             // GTO
    case 0xd5:                                             // GTO
    case 0xd6:                                             // GTO
    case 0xd7:                                             // GTO
    case 0xd8:                                             // GTO
    case 0xd9:                                             // GTO
    case 0xda:                                             // GTO
    case 0xdb:                                             // GTO
    case 0xdc:                                             // GTO
    case 0xdd:                                             // GTO
    case 0xde:                                             // GTO
    case 0xdf:                                             // GTO
         addr = GtoXeq(addr+1);
         if (addr == 0) {
           running = 0;
           addr = oaddr;
           }
         break;

    case 0xe0:                                             // XEQ
    case 0xe1:                                             // XEQ
    case 0xe2:                                             // XEQ
    case 0xe3:                                             // XEQ
    case 0xe4:                                             // XEQ
    case 0xe5:                                             // XEQ
    case 0xe6:                                             // XEQ
    case 0xe7:                                             // XEQ
    case 0xe8:                                             // XEQ
    case 0xe9:                                             // XEQ
    case 0xea:                                             // XEQ
    case 0xeb:                                             // XEQ
    case 0xec:                                             // XEQ
    case 0xed:                                             // XEQ
    case 0xee:                                             // XEQ
    case 0xef:                                             // XEQ
         addr = GtoXeq(addr+1);
         if (addr == 0) {
           running = 0;
           addr = oaddr;
           }
         else {
           if (running) {
             Push((oaddr-1)-isize(oaddr-1));
             }
           else {
             running = -1;
             for (i=0; i<7; i++) ram[REG_A+i] = 0;
             for (i=2; i<7; i++) ram[REG_B+i] = 0;
             }
           }
         break;

    case 0xf0:                                             // TEXT 0
         for (i=REG_M; i<=REG_P+2; i++)
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
         if (ram[addr] != 0x7f) {
           for (i=REG_M; i<=REG_P+2; i++)
             ram[i] = 0;
           }
         for (i=0; i<(cmd & 0x0f); i++) {
           if (i > 0 || ram[addr] != 0x7f) {
             for (j=REG_P+2; j>REG_M; j--)
               ram[j] = ram[j-1];
             ram[REG_M] = ram[addr--];
             } else addr--;
           }
         break;

    }
  if (ram[PENDING] != 'N') ram[LIFT] = ram[PENDING];
  if (debug) ShowStatRegs(0);
  if (singleStep) {
    printf(":");
    fgets(buffer,2,stdin);
    }
  errFlag = 0;
  return addr;
  }

