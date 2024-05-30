#include "header.h"

int FindStart(int address) {
  int addr;
  int byt;
  int reg;
  int flag;
  int l;
  while (ram[address] < 0xc0 || ram[address] >= 0xce)
    address -= isize(address);

  flag = -1;
  while (flag) {
    l = ((ram[address] & 0x0f) << 8) | ram[address-1];
    if (l == 0x00) {
      address = (ram[REG_C+2] << 4) | ((ram[REG_C+1] &0xf0) >> 4);
      address *= 7;
      address--;
      flag = 0;
      }
    else {
      reg = l & 0x1ff;
      byt = (l >> 9) & 0x7;
      addr = reg * 7 + byt;
      address += addr;
      address--;
      if (ram[address-2] < 0xf0) {
        address -= 3;
        flag = 0;
        }
      }
    }
  return address;
  }

