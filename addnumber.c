#include "header.h"

void AddNumber(char n) {
  int i;
  int t;
  NUMBER x;
  if (FlagSet(22) == 0) {
    dp = 0;
    SetFlag(22);
    x.sign = 0;
    x.esign = 0;
    for (i=0; i<10; i++) x.mantissa[i] = 0;
    x.exponent[0] = 0;
    x.exponent[1] = 0;
    if (n < 10) {
      x.mantissa[0] = n;
      ram[REG_E*7+2] &= 0xf0;
      ram[REG_E*7+2] |= 0x01;
      ram[REG_E*7+1] &= 0x0f;
      }
    if (n == 10) {
      ram[REG_E*7+2] &= 0xf0;
      ram[REG_E*7+2] |= 0x00;
      ram[REG_E*7+1] &= 0x0f;
      ram[REG_E*7+1] |= 0x10;
      x.esign = 9;
      x.exponent[1] = 1;
      }
    if (n == 11) {
      ram[REG_E*7+2] &= 0xf0;
      ram[REG_E*7+2] |= 0x00;
      ram[REG_E*7+1] &= 0x0f;
      ram[REG_E*7+1] |= 0x20;
      x.mantissa[0] = 1;
      }
    StoreNumber(x, REG_X);
    return;
    }
  if (n < 10) {
    x = RecallNumber(REG_X);
    if (ram[REG_E*7+1] &0x20) {
      if ((ram[REG_E*7+2] & 0x0f) == 0) {
        x.exponent[1] = n;
        ram[REG_E*7+2]++;
        }
      if ((ram[REG_E*7+2] & 0x0f) == 1) {
        x.exponent[0] = x.exponent[1];
        x.exponent[1] = n;
        ram[REG_E*7+2]++;
        }
      }
    else {
      if ((ram[REG_E*7+2] & 0x0f) < 10) {
        x.mantissa[ram[REG_E*7+2] & 0x0f] = n;
        ram[REG_E*7+2]++;
        if ((ram[REG_E*7+1] & 0x10) == 0) {
          x.exponent[1]++;
          if (x.exponent[1] >= 10) {
            x.exponent[0]++;
            x.exponent[1] = 0;
            }
          }
        }
      }
    StoreNumber(x, REG_X);
    }
  if (n == 10) {
    ram[REG_E*7+1] |= 0x10;
    }
  if (n == 11) {
    if ((ram[REG_E*7+1] & 0x20) == 0x00) {
      ram[REG_E*7+1] |= 0x20;
      }
    }
  if (n == 12) {
    x = RecallNumber(REG_X);
    if (ram[REG_E*7+1] & 0x20)
      x.esign = (x.esign == 0) ? 9 : 0;
    else
      x.sign = (x.sign == 0) ? 9 : 0;
    StoreNumber(x,REG_X);
    }
  }

// 10 = .
// 11 = EEX
// 12 = CHS
// e.1 
//   1x - decimal entered
//   2x - eex entered
