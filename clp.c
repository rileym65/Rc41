#include "header.h"

void Clp(char* name) {
  int i;
  int address;
  int size;
  address = FindGlobal(name);
  if (address == 0) return;
  address = FindStart(address);
  while (ram[address] < 0xc0 || ram[address] > 0xcd || ram[address-2] >= 0xf0) {
    if (ram[address] >= 0xc0 && ram[address] <=0xcd && ram[address-2] >= 0xf0 && ram[address-3] != 0x00) {
      SetKaFlag(ram[address-3], 0);
      }
    size = isize(address);
    for (i=0; i<size; i++)
      ram[address--] = 0x00;
    }
  if ((ram[address-2] & 0xf0) != 0x20) {
    for (i=0; i<3; i++)
      ram[address--] = 0x00;
    }

  ReLink();
  Pack();
  }

