#include "header.h"

void GtoEnd() {
  int end;
  int adr;
  int ptr;
  end = ((ram[REG_C+1] & 0x0f) << 8) | (ram[REG_C+0] & 0xff);
  end *= 7;
  adr = end + 3;
  while (ram[adr] == 0x00) adr++;
  if (ram[adr+2] < 0xc0 || ram[adr+2] > 0xcd || ram[adr] >= 0xf0) {
    ptr = ((ram[end+2] & 0x0f) << 8) | ram[end+1];
    ram[end-7] = 0x2d;
    ram[end-6] = 0x01;
    ram[end-5] = 0xc2;
    ram[end+2] = 0xc0 | ((ptr & 0xf00) >> 8);
    ram[end+1] = ptr & 0xff;
    ram[end] = 0x0d;
    end -= 7;
    end /= 7;
    ram[REG_C+1] &= 0xf0;
    ram[REG_C+1] |= ((end >> 8) & 0x0f);
    ram[REG_C+0] = end & 0xff;
    }
  }

