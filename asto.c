#include "header.h"

void Asto(int rreg) {
  int i;
  int p;
  int l;
  int reg;
  int base;
  NUMBER n;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  if (rreg < 0x70) {
    reg = base + rreg;
    }
  else if (rreg >= 0x70 && rreg <= 0x7f) reg = rreg - 0x70;
  else if (rreg >= 0x80 && rreg <= 0xef) {
    reg = base + (rreg - 0x80);
    if (reg > 0xfff) {
      Message("NONEXISTENT");
      return;
      }
    reg = base + ToInteger(RecallNumber(reg));
    }
  else if (rreg >= 0xf0 && rreg <= 0xff) {
    reg = base + ToInteger(RecallNumber(rreg - 0xf0));
    }
  if (reg > 0xfff) {
    Message("NONEXISTENT");
    return;
    }
  reg *= 7;
  p = (REG_P) + 2;
  while (p > (REG_M) && ram[p] == 0) p--;
  if (p == (REG_M) && ram[p] == 0) {
    ram[reg+6] = 0xf0;
    for (i=0; i<6; i++) ram[reg+i] = 0x00;
    }
  else {
    l = p - (REG_M) + 1;
    if (l > 6) l = 6;
    for (i=0; i<6; i++) ram[reg+i] = 0x00;
    i = 5;
    ram[reg+6] = 0xf0 + l;
    while (l > 0) {
      ram[reg+i] = ram[p--];
      i--;
      l--;
      }
    }
  }

