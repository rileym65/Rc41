#include "header.h"

int FindNextGlobal(int address) {
  int pend;
  int addr;
  int byt;
  int reg;
  int flag;
  int l;
  while (ram[address] < 0xc0 || ram[address] >= 0xce)
    address -= isize(address);
  return address;
  }

