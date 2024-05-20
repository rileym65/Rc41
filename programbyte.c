#include "header.h"

void ProgramByte(byte b) {
  int i;
  int addr;
  int adr;
  int byt;
  int reg;
  int lineNumber;
  int pqr;
  addr = (ram[REG_B*7+1] << 8) | ram[REG_B*7+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
// **********************************************************
// This needs to go at the beginning of inserting instruction
// **********************************************************
//  lineNumber = ram[REG_E*7+0] + ((ram[REG_E*7+1] &0x0f) << 8);
//  if (lineNumber == 0) {
//    adr--;
//    }
//  else {
//    adr--;
//    while (ram[adr] == 0) adr--;
//    if (((ram[adr] & 0xf0) != 0xc0) || ((ram[adr-2] & 0xf0) != 0x20)) {
//      adr -= isize(adr);
//      }
//    }
  if (ram[adr] != 0) {
    pqr = ((ram[REG_C*7+1] & 0x0f) << 8) | ram[REG_C*7+0];
    pqr *= 7;
    while (pqr < adr) {
      ram[pqr-7] = ram[pqr];
      }
    }
  ram[adr--] = b;
  reg = adr / 7;
  byt = adr % 7;
  addr = (byt << 12) | reg;
  ram[REG_B*7+1] = (addr >> 8) & 0xff;
  ram[REG_B*7+0] = addr & 0xff;
  }

