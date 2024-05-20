#include "header.h"

int FlagSet(int f) {
  int offset;
  offset = 6 - (f / 8);
  f = f & 7;
  f = 0x80 >> f;
  if ((ram[REG_D*7+offset] & f) == 0) return 0;
  return -1;
  }

