#include "header.h"

void Clp(char* name) {
  int s;
  int i;
  int is;
  int address;
  int end;
  int size;
  int regs;
  int bytes;
  address = FindGlobal(name);
  if (address == 0) return;
  address = FindStart(address);
  end = FindEnd(address);
  size = 0;
  printf("\n");
  while (ram[address] == 0x00) address--;
  while (address >= end) {
    if (ram[address] >= 0xc0 && ram[address] <=0xcd && ram[address-2] >= 0xf0 && ram[address-3] != 0x00) {
      SetKaFlag(ram[address-3], 0);
      }
    if (ram[address] >= 0xc0 && ram[address] <=0xcd) {
      s = ((ram[address] & 0x0f) <<8) | ram[address-1];
      size += (((s & 0x1ff) * 7) + (s >> 9));
      size--;
      }
    is = isize(address);
    for (i=0; i<is; i++) ram[address--] = 0x00;
    while (ram[address] == 0x00) address--;
    }
  while (ram[address] < 0xc0 || ram[address] > 0xcd) address--;
  s = ((ram[address] & 0x0f) <<8) | ram[address-1];
  size += (((s & 0x1ff) * 7) + (s >> 9));
  regs = size / 7;
  bytes = size % 7;
  ram[address] &= 0xf0;
  ram[address] |= (bytes << 1) | ((regs >> 8) & 1);
  ram[address-1] = regs & 0xff;
  if (ram[address-2] < 0xf0) {
    ram[address-2] |= 0x0d;
    }
  else {
    i = -1;
    while (i) {
      while (ram[address] < 0xc0 || ram[address] > 0xcd) address--;
      if (ram[address-2] < 0xf0) i = 0;
      else address -= 3;
      }
    ram[address-2] |= 0x0d;
    }
  Pack();
  }

