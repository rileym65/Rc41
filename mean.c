#include "header.h"

void Mean() {
  int base;
  int ofs;
  NUMBER x;
  NUMBER y;
  base = ram[REG_C*7+2] << 4;
  base |= ((ram[REG_C*7+1] >> 4) & 0xf);
  ofs = ram[REG_C*7+6] << 4;
  ofs |= ((ram[REG_C*7+5] >> 4) & 0xf);
  base += ofs;
  x = RecallNumber(REG_X);
  StoreNumber(x, REG_L);
  y = RecallNumber(base+0);
  x = RecallNumber(base+5);
  if (IsZero(x)) {
    Message("DATA ERROR");
    return;
    }
  x = Div(y, x);
  StoreNumber(x, REG_X);
  y = RecallNumber(base+2);
  x = RecallNumber(base+5);
  x = Div(y, x);
  StoreNumber(x, REG_Y);
  }

