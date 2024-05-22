#include "header.h"

void FixLineNumber() {
  int addr;
  int ladr;
  int lineNumber = 0;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  addr = FromPtr(addr);
  addr--;
  ladr = FindStart(addr);
  while (ladr != addr) {
    ladr -= isize(ladr);
    if (ram[ladr] != 0) lineNumber++;
    }
  if (lineNumber == 0) lineNumber = 1;
  ram[REG_E+1] &= 0xf0;
  ram[REG_E+1] |= ((lineNumber >> 8) & 0x0f);
  ram[REG_E+0] = lineNumber & 0xff;
  }

