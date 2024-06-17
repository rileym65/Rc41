#include "header.h"

void Size(char* token) {
  int end;
  int r00;
  int new;
  int n;
  int dst;
  int src;
  int dif;
  n = atoi(token);
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] & 0xf0) >> 4);
  new = RAMTOP - n;
printf("end = %x\n",end);
printf("r00 = %x\n",r00);
  dif = new - r00;
printf("Dif = %d\n",dif);
  if (dif > 0) {
    dst = 0x1ff * 7 + 6;
    src = (0x1ff - dif) * 7 + 6;
    while (src >= (0x0c0 * 7)) ram[dst--] = ram[src--];
    while (dst >= (0x0c0 * 7)) ram[dst--] = 0x00;
    r00 += dif;
    end += dif;
    }
  else {
    dif = -dif;
    dst = 0x0c0 * 7;
    src = (0x0c0 + dif) * 7;
    while (src <= (0x1ff * 7 + 6)) ram[dst++] = ram[src++];
    while (dst <= (0x1ff * 7 + 6)) ram[dst++] = 0x00;
    r00 -= dif;
    end -= dif;
    }
  ram[REG_C+2] = (r00 >> 4) & 0xff;
  ram[REG_C+1] = ((r00 & 0x0f) << 4) | ((end >> 8) & 0x0f);
  ram[REG_C+0] = end & 0xff;
  }

