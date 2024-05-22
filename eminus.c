#include "header.h"

void EMinus() {
  int base;
  int ofs;
  NUMBER x;
  NUMBER y;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  ofs = ram[REG_C+6] << 4;
  ofs |= ((ram[REG_C+5] >> 4) & 0xf);
  base += ofs;
  a = RecallNumber(base);
  x = RecallNumber(R_X);
  c = Sub(a,x);
  StoreNumber(c, base);
  a = RecallNumber(base+1);
  c = Mul(x,x);
  a = Sub(a,c);
  StoreNumber(a, base+1);
  a = RecallNumber(base+2);
  y = RecallNumber(R_Y);
  c = Sub(a,y);
  StoreNumber(c, base+2);
  a = RecallNumber(base+3);
  c = Mul(y,y);
  a = Sub(a,c);
  StoreNumber(c, base+3);
  a = RecallNumber(base+4);
  c = Mul(x,y);
  a = Sub(a,c);
  StoreNumber(a,base+4);
  a = RecallNumber(base+5);
  a = Sub(a,ONE);
  StoreNumber(a,base+5);
  StoreNumber(a,R_X);
  }

