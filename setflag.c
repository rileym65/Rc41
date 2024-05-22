#include "header.h"

void SetFlag(int f) {
  int offset;
  offset = 6 - (f / 8);
  f = f & 7;
  f = 0x80 >> f;
  ram[REG_D+offset] |= f;
  }

