#include "header.h"

/* **************************************************** */
/* ***** Relink global chain                      ***** */
/* **************************************************** */
void ReLink() {
  int end;
  int count;
  int last;
  int len;
  int regs;
  int bytes;
  int address;
  int first;
  end = 0;
  count = 0;
  address = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  address *= 7;
  last = address;
  first = -1;
  address++;
  while (end == 0) {
    if (ram[address] >= 0xc0 && ram[address] <= 0xcd && count > 0) {
      len = last - address;
      regs = len / 7;
      bytes = len % 7;
      len = (bytes << 9) | (regs & 0x1ff);
      if (first) len = 0;
      first = 0;
      ram[address] &= 0xf0;
      ram[address] |= ((len >> 8) & 0x0f);
      ram[address-1] = len & 0xff;
      if ((ram[address-2] & 0xf0) == 0x20) end = -1;
      else {
        last = address+1;
        count = isize(address);
        address -= isize(address);
        }
      }
    else {
      count += isize(address);
      address -= isize(address);
      }
    }
  }

