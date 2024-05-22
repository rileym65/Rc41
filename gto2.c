#include "header.h"

int Gto2(int address) {
  int addr;
  int last;
  int jump;
  int ret;
  int ofs;
  int dif;
  byte lbl;
  int flag;
  int lineNumber;
printf("gto2: %02x %02x %02x\n",ram[address],ram[address-1],ram[address-2]);
  lbl = ram[address] & 0x0f;
  address--;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  addr = FromPtr(addr) - 1;
  if (address >= 0x0c0 && ram[addr-1] != 0) {
printf("has jump offset\n");
    addr--;
    jump = (ram[addr] & 0x0f) * 7;
    jump += ((ram[addr] >> 4) & 0x7);
    if (ram[addr] < 0x80) jump = -jump;
    addr += jump;
    ret = addr-1;
    addr = ToPtr(addr);
    ram[REG_B+1] = (addr >> 8) & 0xff;
    ram[REG_B+0] = addr & 0xff;
    ram[REG_E+0] = 0xff;
    ram[REG_E+1] |= 0x0f;
    return ret;
    }
else printf("No jump offset\n");
  last = addr;
  flag = -1;
  while (flag) {
    if (ram[addr] == lbl) flag = 0;
    else if (ram[addr] >= 0xc0 && ram[addr] <= 0xcd &&
             ram[addr-2] < 0xf0) {
      addr = FindStart(addr) + 1;
      }
    else {
      addr -= isize(addr);
      }
    if (flag != 0 && addr == last) {
printf("Not found\n");
      Message("NONEXISTENT");
      return 0;
      }
    }
  addr++;
  if (address >= 0x0c0) {
    }
  dif = (last-1)-addr;
  ofs = 0;
  if (dif < 0) {
    dif = -dif;
    ofs = 0x80;
    }
  if (dif > 112) {
    dif = 0;
    ofs = 0;
    }
  ofs |= (dif / 7);
  ofs |= ((dif % 7) << 4);
printf("found [%04x] %02x %02x %02x\n",addr,ram[addr], ram[addr-1], ram[addr-2]);
printf("last  [%04x] %02x %02x %02x\n",last,ram[last], ram[last-1], ram[last-2]);
printf("Offset: %02x\n",ofs);
  ram[last-1] = ofs;
  ret = addr-1;
  addr = ToPtr(addr);
  ram[REG_B+1] = (addr >> 8);
  ram[REG_B+0] = addr & 0xff;
  ram[REG_E+0] = 0xff;
  ram[REG_E+1] |= 0x0f;
  return ret;
  }

