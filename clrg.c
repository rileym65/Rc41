#include "header.h"

void Clrg() {
  int base;
  int ofs;
  NUMBER x;
  NUMBER y;
  base = ram[REG_C*7+2] << 4;
  base |= ((ram[REG_C*7+1] >> 4) & 0xf);
  while (base <= 0xfff) {
    StoreNumber(ZERO, base);
    base++;
    }
  }

