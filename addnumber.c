#include "header.h"

void AddNumber(char n) {
  int i;
  int p;
  p = -1;
  NUMBER x;
  ram[PENDING] = 'D';
  if (FlagSet(22) == 0) {
    for (i=REG_P+3; i<REG_R; i++) ram[i] = 0xff;
    ram[REG_E+1] &= 0x0f;
    ram[REG_E+2] |= 0x0f;
    SetFlag(22);
    }
  if (n < 10) {                                       /* digit */
    if (ram[REG_P+5] == 11) {
      if (ram[REG_P+4] == 0xff) ram[REG_P+4] = n;
      else if (ram[REG_P+3] == 0xff) ram[REG_P+3] = n;
      }
    else {
      p = 0;
      while (p < 10 && ram[REG_Q+6-p] != 0xff) p++;
      if (p < 10) ram[REG_Q+6-p] = n;
      }
    }
  if (n == 11) {                                      /* EEX */
    if (ram[REG_P+5] == 0xff) ram[REG_P+5] = 11;
    }
  if (n == 12) {                                      /* CHS */
    if (ram[REG_P+5] == 11) ram[REG_E+1] ^= 0x20;
      else ram[REG_E+1] ^= 0x10;
    }
  if (n == 10) {                                      /* . */
    if ((ram[REG_E+2] & 0x0f) == 0x0f && ram[REG_P+5] != 11) {
      p = 0;
      while (p < 10 && ram[REG_Q+6-p] != 0xff) p++;
      ram[REG_E+2] &= 0xf0;
      ram[REG_E+2] |= p;
      }
    }

  }

// 10 = .
// 11 = EEX
// 12 = CHS
// e.1 
//   1x - decimal entered
//   2x - eex entered
