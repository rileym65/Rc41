#include "header.h"

void Cle() {
  int i;
  int base;
  int ofs;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  ofs = ram[REG_C+6] << 4;
  ofs |= ((ram[REG_C+5] >> 4) & 0xf);
  base += ofs;
  for (i=0; i<6; i++)
    StoreNumber(ZERO, base+i);
  }

