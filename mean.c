#include "header.h"

void Mean() {
  int base;
  int ofs;
  NUMBER x;
  NUMBER y;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  ofs = ram[REG_C+6] << 4;
  ofs |= ((ram[REG_C+5] >> 4) & 0xf);
  base += ofs;
  x = RecallNumber(R_X);
  StoreNumber(x, R_L);
  y = RecallNumber(base+0);
  x = RecallNumber(base+5);
  if (IsZero(x)) {
    Message("DATA ERROR");
    return;
    }
  x = Div(y, x);
  StoreNumber(x, R_X);
  y = RecallNumber(base+2);
  x = RecallNumber(base+5);
  x = Div(y, x);
  StoreNumber(x, R_Y);
  }

