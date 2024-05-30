#include "header.h"

void Arcl(int rreg) {
  int i;
  int p;
  int reg;
  int base;
  char buffer[32];
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
  for (i=0; i<32; i++) buffer[i] = 0;
  if (ram[reg * 7 + 6] >= 0xf0) {
    for (i=0; i<8; i++) buffer[i] = 0;
    for (i=0; i<ram[reg * 7 + 6]-0xf0; i++)
      buffer[i] = ram[reg * 7 +5 - i];
    }
  else {
    n = RecallNumber(reg);
    Format(n, buffer);
    while (buffer[0] == ' ') {
      for (i=0; i<31; i++) buffer[i] = buffer[i+1];
      }
    }
  p = 0;
  while (buffer[p] != 0) {
    for (i=(REG_P+2); i>(REG_M); i--) ram[i] = ram[i-1];
    ram[REG_M] = buffer[p++];
    }
  }

