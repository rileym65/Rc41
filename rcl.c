#include "header.h"

NUMBER Rcl(int rreg) {
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
      return ZERO;
      }
    reg = base + ToInteger(RecallNumber(reg));
    }
  else if (rreg >= 0xf0 && rreg <= 0xff) {
    reg = base + ToInteger(RecallNumber(rreg - 0xf0));
    }
  if (reg > 0xfff) {
    Message("NONEXISTENT");
    return ZERO;
    }
  return RecallNumber(reg);
  }

