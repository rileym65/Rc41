#include <math.h>
#include "header.h"

/* sqrt((x^2 - x*meanX)/(n-1)) */

void Sdev() {
  int base;
  int ofs;
  NUMBER a;
  NUMBER x;
  NUMBER x2;
  NUMBER n;
  NUMBER meanx;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  ofs = ram[REG_C+6] << 4;
  ofs |= ((ram[REG_C+5] >> 4) & 0xf);
  base += ofs;
  a = RecallNumber(R_X);
  StoreNumber(a, R_L);

  x = RecallNumber(base+0);
  x2 = RecallNumber(base+1);
  n = RecallNumber(base+5);
  if (n.sign != 0 && n.sign != 9) {
    Message("ALPHA DATA");
    Error();
    return;
    }
  if (x.sign != 0 || IsZero(n) || IsZero(Sub(n, S_ONE))) {
    Message("DATA ERROR");
    Error();
    return;
    }
  meanx = Div(x, n);
//  x = sqrt((x2 - (x * meanx)) / (n - 1));
  x = Sqrt(Div(Sub(x2,(Mul(x,meanx))),(Sub(n,S_ONE))) );
  StoreNumber(x, R_X);

  x = RecallNumber(base+2);
  x2 = RecallNumber(base+3);
  meanx = Div(x, n);
//  x = sqrt((x2 - (x * meanx)) / (n - 1));
  x = Sqrt(Div(Sub(x2,(Mul(x,meanx))),(Sub(n,S_ONE))) );
  StoreNumber(x, R_Y);
  }

