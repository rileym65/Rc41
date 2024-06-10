#include "header.h"

int GtoXeqInd(int address) {
  int addr;
  int last;
  int ret;
  byte lbl;
  int flag;
  NUMBER n;
  lbl = ram[address-1] & 0x7f;
  n = Rcl(lbl);
  lbl = ToInteger(n);
  address--;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  addr = FromPtr(addr) - 1;
  last = addr;
  flag = -1;
  while (flag) {
    if (lbl < 15 && ((ram[addr-1] & 0x7f) == lbl+1)) flag = 0;
    else if (lbl > 14 && (ram[addr] == 0xcf) && ((ram[addr-1] & 0x7f) == lbl)) flag = 0;
    else if (ram[addr] >= 0xc0 && ram[addr] <= 0xcd &&
             ram[addr-2] < 0xf0) {
      addr = FindStart(addr) + 1;
      }
    else {
      addr -= isize(addr);
      }
    if (flag != 0 && addr == last) {
      Message("NONEXISTENT");
      Error();
      return 0;
      }
    }
  addr++;
  if (lbl < 15) ret = addr - 2;
    else ret = addr-1;
  addr = ToPtr(addr);
  ram[REG_B+1] = (addr >> 8);
  ram[REG_B+0] = addr & 0xff;
  ram[REG_E+0] = 0xff;
  ram[REG_E+1] |= 0x0f;
  return ret;
  }

