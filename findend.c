#include "header.h"

int FindEnd(int address) {
  while (ram[address] < 0xc0 || ram[address] >= 0xce || ram[address-2] >= 0xf0)
    address -= isize(address);
  return address;
  }

