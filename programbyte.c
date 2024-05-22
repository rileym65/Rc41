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
  if (ram[adr] != 0) {
    pqr = ((ram[REG_C*7+1] & 0x0f) << 8) | ram[REG_C*7+0];
    pqr *= 7;
    pqr -= 7;
    while (pqr < adr) {
      ram[pqr] = ram[pqr+7];
      pqr++;
      }
    for (i=0; i<7; i++) ram[adr-i] = 0;
    pqr = ((ram[REG_C*7+1] & 0x0f) << 8) | ram[REG_C*7+0];
    pqr--;
    ram[REG_C*7+0] = pqr & 0xff;
    ram[REG_C*7+1] &= 0xf0;
    ram[REG_C*7+1] |= ((pqr >> 8) & 0x0f);
    byteCount += 7;
    }
  ram[adr--] = b;
  reg = adr / 7;
  byt = adr % 7;
  addr = (byt << 12) | reg;
  ram[REG_B*7+1] = (addr >> 8) & 0xff;
  ram[REG_B*7+0] = addr & 0xff;
  }

