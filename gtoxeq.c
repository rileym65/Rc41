#include "header.h"

int GtoXeq(int address) {
  int addr;
  int last;
  int jump;
  int ret;
  int ofs;
  int dif;
  byte lbl;
  int flag;
  int lineNumber;
  if (address >= 0x0c0)
    lbl = ram[address-2] & 0x7f;
  else
    lbl = ((ram[REG_E+2] & 0x0f) << 4) | ((ram[REG_E+1] >> 4) & 0x0f);
printf("Searching for %02x\n",lbl);
  address--;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  addr = FromPtr(addr) - 1;
  if (address >= 0x0c0 && ram[addr-1] != 0) {
    jump = ((ram[addr] * 0x0f) << 8) | ram[addr-1];
    jump = ((jump & 0x1ff) * 7) + ((jump >> 9) & 0x07);
    if (ram[addr-2] < 0x80) jump = -jump;
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
      return 0;
      }
    }
  addr++;
  if (address >= 0x0c0) {
    dif = (last)-(addr);
    ofs = 0;
    if (dif < 0) {
      dif = -dif;
      ram[last-2] |= 0x80;
      }
    if (dif > 511) {
      dif = 0;
      ofs = 0;
      }
    if (dif != 0) {
      ofs |= (dif / 7);
      ofs |= ((dif % 7) << 9);
      ram[last] &= 0xf0;
      ram[last] |= (ofs >> 8) & 0x0f;
      ram[last-1] = ofs & 0xff;
      }
    }
  if (lbl < 15) ret = addr - 2;
    else ret = addr-1;
  addr = ToPtr(addr);
  ram[REG_B+1] = (addr >> 8);
  ram[REG_B+0] = addr & 0xff;
  ram[REG_E+0] = 0xff;
  ram[REG_E+1] |= 0x0f;
  return ret;
  }

