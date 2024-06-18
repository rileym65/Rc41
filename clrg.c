#include "header.h"

void Clrg() {
  int base;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  while (base <= 0x1ff) {
    StoreNumber(ZERO, base);
    base++;
    }
  }

