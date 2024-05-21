#include "header.h"

void GotoLine(int line) {
  int addr;
  int adr;
  int byt;
  int reg;
  int flag;
  int l;
  addr = (ram[REG_B*7+1] << 8) | ram[REG_B*7+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  adr--;
printf("address: %x\n",adr);
  while (ram[adr] < 0xc0 || ram[adr] >= 0xce)
    adr -= isize(adr);
printf("%02x %02x %02x\n",ram[adr], ram[adr-1], ram[adr-2]);
  flag = -1;
  while (flag) {
    if (((ram[adr] & 0x0f) == 0) && (ram[adr-1] == 0x00)) flag = 0;
    else if (ram[adr-2] < 0xf0) flag = 0;
    else {
printf("found label instead of end\n");
      }
    }
  if (((ram[adr] & 0x0f) == 0) && (ram[adr-1] == 0x00)) {
    reg = (ram[REG_C*7+2] << 4) | ((ram[REG_C*7+1] &0xf0) >> 4);
    adr = reg * 7;
    }
  else {
    adr -= 2;
    }
printf("address: %x\n",adr);
  if (line > 1) {
    l = line;
    line = 1;
    while (l > 1) {
      while (ram[adr-1] == 0) adr--;
printf("%d: [%x] %02x\n",line,adr,ram[adr-1]);
      if (ram[adr-1] >= 0xc0 && ram[adr-1] < 0xce && ram[adr-3] < 0xf0) l = 0;
      else {
        adr -= isize(adr-1);
        line++;
        l--;
        }
      }
printf("final line: %d\n",line);
    }
  reg = adr / 7;
  byt = adr % 7;
  addr = reg | (byt << 12);
  ram[REG_B*7+1] = (addr >> 8) & 0xff;
  ram[REG_B*7+0] = addr & 0xff;
  ram[REG_E*7+0] = line & 0xff;
  ram[REG_E*7+1] &= 0xf0;
  ram[REG_E*7+1] |= ((line >> 8) & 0x0f);
  }

