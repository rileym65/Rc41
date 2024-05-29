#include "header.h"

int Skip(int addr) {
  while (ram[addr] == 0x00) addr--;
  addr -= isize(addr);
  return addr;
  }

