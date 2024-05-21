#include "header.h"

void ProgramStep(char* line) {
  int i;
  int addr;
  int adr;
  int byt;
  int reg;
  int start;
  int lineNumber;
  addr = (ram[REG_B*7+1] << 8) | ram[REG_B*7+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  lineNumber = ram[REG_E*7+0] + ((ram[REG_E*7+1] &0x0f) << 8);
  if (lineNumber == 0) {
    adr--;
    }
  else {
    adr--;
    while (ram[adr] == 0) adr--;
    if (((ram[adr] & 0xf0) != 0xc0) || ((ram[adr-2] & 0xf0) != 0xf0)) {
      adr -= isize(adr);
      }
    }
  start = adr+1;
  reg = adr / 7;
  byt = adr % 7;
  addr = (byt << 12) | reg;
  ram[REG_B*7+1] = (addr >> 8) & 0xff;
  ram[REG_B*7+0] = addr & 0xff;
  ProgramByte(ram[REG_R*7+1]);
  if (isize(REG_R*7+1) > 1) {
    ProgramByte(ram[REG_R*7+0]);
    }
  reg = start / 7;
  byt = start % 7;
  addr = (byt << 12) | reg;
  ram[REG_B*7+1] = (addr >> 8) & 0xff;
  ram[REG_B*7+0] = addr & 0xff;
  lineNumber++;
  ram[REG_E*7+0] = lineNumber & 0xff;
  ram[REG_E*7+1] &= 0xf0;
  ram[REG_E*7+1] |= ((lineNumber >> 8) & 0x0f);

  }

