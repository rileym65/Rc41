#include "header.h"

/* *********************************************** */
/* ***** Convert ram address to NABC address ***** */
/* *********************************************** */
int ToPtr(int addr) {
  int reg;
  int byt;
  reg = addr / 7;
  byt = addr % 7;
  return (reg & 0xfff) | (byt << 12);
  }

