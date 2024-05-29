#include "header.h"

void Init() {
  int mno;
  int pqr;
  int i;
  running = 0;
  on = -1;
  for (i=0; i<RAMSIZE; i++)
    ram[i] = 0;
  mno = 0x0c0 + 46;
  pqr = mno - 1;
  ram[REG_B+0] = mno & 0xff;
  ram[REG_B+1] = 0x00 | ((mno >> 8) & 0xf);
  ram[REG_C+0] = pqr & 0xff;
  ram[REG_C+1] = ((pqr >> 8) & 0xf) | ((mno & 0xf) << 4);
  ram[REG_C+2] = (mno >> 4) & 0xff;
  ram[REG_C+3] = 0x69;
  ram[REG_C+4] = 0x01;
  ram[REG_C+5] = 0xb0;
  ram[REG_C+6] = 0x00;
  ram[pqr*7+0] = 0x29;
  ram[pqr*7+1] = 0x00;
  ram[pqr*7+2] = 0xc0;
  SetFlag(28);
  SetFlag(29);
  SetFlag(37);
  SetFlag(40);
  ZERO.sign = 0;
  ZERO.esign = 0;
  for (i=0; i<10; i++) ZERO.mantissa[i] = 0;
  for (i=0; i<2; i++) ZERO.exponent[i] = 0;
  PI = AtoN("3.141592654");
  ONE = AtoN("1");
  TEN = AtoN("10");
  NEGONE = AtoN("-1");
  DTOR = AtoN("1.74532925199433E-2");
  RTOD = AtoN("5.72957795130823E+1");
  GTOR = AtoN("0.015707963268");
  RTOG = AtoN("63.661977236758");
  E = AtoN("2.718281828459");
  LOGE = AtoN("4.3429448E-1");
  }

