#include "header.h"

int FindNextGlobal(int address) {
  while (ram[address] < 0xc0 || ram[address] >= 0xce)
    address -= isize(address);
  return address;
  }

