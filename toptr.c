#include "header.h"

int ToPtr(int addr) {
  int reg;
  int byt;
  reg = addr / 7;
  byt = addr % 7;
  return (reg & 0xfff) | (byt << 12);
  }

