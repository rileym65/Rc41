#include "header.h"

int Gto2(int address) {
  int addr;
  int last;
  int jump;
  int ret;
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
    if (ram[addr] >= 0x80) jump = -jump;
    addr += jump;
    ret = addr;
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
  ret = addr;
  addr = ToPtr(addr);
  ram[REG_B+1] = (addr >> 8);
  ram[REG_B+0] = addr & 0xff;
  ram[REG_E+0] = 0xff;
  ram[REG_E+1] |= 0x0f;
  return addr;
  }

