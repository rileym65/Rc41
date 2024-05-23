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
  lbl = ram[address] & 0x0f;
  address--;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  addr = FromPtr(addr) - 1;
  if (address >= 0x0c0 && ram[addr-1] != 0) {
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
  ram[last-1] = ofs;
  ret = addr-1;
  addr = ToPtr(addr);
  ram[REG_B+1] = (addr >> 8);
  ram[REG_B+0] = addr & 0xff;
  ram[REG_E+0] = 0xff;
  ram[REG_E+1] |= 0x0f;
  return ret;
  }

