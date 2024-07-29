#include "header.h"

void EndNumber() {
  int i;
  int p;
  int e;
  int d;
  NUMBER nm;
  if (!FlagSet(22)) return;
  ClearFlag(22);
  nm.sign = (ram[REG_E+1] & 0x10) ? 9 : 0;
  i = REG_Q+6;
  p = 0;
  e = -1;
  d = ram[REG_E+2] & 0x0f;
  while (p < 10 && ram[i] < 10) {
    nm.mantissa[p++] = ram[i--];
    if (p <= d) e++;
    }
  while (p < 10) nm.mantissa[p++] = 0x00;
  while (nm.mantissa[0] == 0x00) {
    for (i=0; i<9; i++) nm.mantissa[i] = nm.mantissa[i+1];
    nm.mantissa[9] = 0;
    e--;
    }
  if (ram[REG_P+5] == 0x0b) {
    if (ram[REG_E+1] & 0x20) {
      if (ram[REG_P+3] == 0xff) e -= ram[REG_P+4];
        else e -= ((ram[REG_P+4] * 10) + ram[REG_P+3]);
      }
    else {
      if (ram[REG_P+3] == 0xff) e += ram[REG_P+4];
        else e += ((ram[REG_P+4] * 10) + ram[REG_P+3]);
      }
    }
  nm.esign = 0;
  if (e < 0) {
    nm.esign = 9;
    e = -e;
    }
  nm.exponent[0] = e / 10;
  nm.exponent[1] = e % 10;
  StoreNumber(nm, R_X);
  ram[LIFT] = 'E';
  }

