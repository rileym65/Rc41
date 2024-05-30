#include "header.h"

int GtoAlpha(int address) {
  int i;
  int n;
  int addr;
  char token[16];

  ram[REG_E+1] |= 0x0f;
  ram[REG_E+0] = 0xff;
  for (i=0; i<(ram[address] & 0xf); i++)
    token[i] = ram[address-1-i];
  token[ram[address] & 0xf] = 0;
  n = FindGlobal(token);
  if (n != 0) {
    addr = n;
    n = ToPtr(n);
    ram[REG_B+1] = (n >> 8) & 0xff;
    ram[REG_B+0] = n & 0xff;
    return addr;
    }
  Message("NONEXISTENT");
  return 0;
  }

