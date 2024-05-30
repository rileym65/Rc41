#include <math.h>
#include "header.h"

/* sqrt((x^2 - x*meanX)/(n-1)) */

void Sdev() {
  int base;
  int ofs;
  NUMBER a;
  char   tmp[32];
  double x,x2,meanx,n;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  ofs = ram[REG_C+6] << 4;
  ofs |= ((ram[REG_C+5] >> 4) & 0xf);
  base += ofs;
  a = RecallNumber(R_X);
  StoreNumber(a, R_L);

  a = RecallNumber(base+0);
  NtoA(a, tmp);
  x = atof(tmp);
  a = RecallNumber(base+1);
  NtoA(a, tmp);
  x2 = atof(tmp);
  a = RecallNumber(base+5);
  NtoA(a, tmp);
  n = atof(tmp);
  if (n == 1) {
    Message("DATA ERROR");
    return;
    }
  meanx = x/n;
  x = sqrt((x2 - (x * meanx)) / (n - 1));
  sprintf(tmp,"%.12e",x);
  a = AtoN(tmp);
  StoreNumber(a, R_X);

  a = RecallNumber(base+2);
  NtoA(a, tmp);
  x = atof(tmp);
  a = RecallNumber(base+3);
  NtoA(a, tmp);
  x2 = atof(tmp);
  if (n == 1) {
    Message("DATA ERROR");
    return;
    }
  meanx = x/n;
  x = sqrt((x2 - (x * meanx)) / (n - 1));
  sprintf(tmp,"%.12e",x);
  a = AtoN(tmp);
  StoreNumber(a, R_Y);
  }

