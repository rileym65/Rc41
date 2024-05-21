#include "header.h"

void ProgramStep(char* line) {
  int i;
  int addr;
  int adr;
  int byt;
  int reg;
  int start;
  int lineNumber;
  if (ram[REG_R*7+1] == 0x00) return;
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
  if (line != NULL) {
    if (strncasecmp(line, "LBL ",4) == 0) {
      ProgramByte(0x00);
      ProgramByte(0xf1);
      ProgramByte(0x00);
      i = 5;
      while (line[i] != 0 && line[i] != '"') {
        ProgramByte(line[i]);
        ram[start-3]++;
        i++;
        }
      }
    if (strncasecmp(line, "GTO ",4) == 0) {
      ProgramByte(0xf0);
      i = 5;
      while (line[i] != 0 && line[i] != '"') {
        ProgramByte(line[i]);
        ram[start-2]++;
        i++;
        }
      }
    if (strcasecmp(line, "END") == 0) {
      ProgramByte(0x00);
      ProgramByte(0x0d);
      }
    }
  else if (isize(REG_R*7+1) > 1) {
    ProgramByte(ram[REG_R*7+0]);
    }
  if (ram[REG_R*7+1] == 0xd0 || ram[REG_R*7+1] == 0xe0) {
    ProgramByte(((ram[REG_E*7+2] & 0x0f) << 4) | 
                ((ram[REG_E*7+1] & 0xf0) >> 4));
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

