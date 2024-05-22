#include "header.h"

int FindGlobal(char* label) {
  int  addr;
  char lbl1[32];
  char lbl2[32];
  int  i;
  int  p;
  int  flag;
  int  dst;
  p = 0;
  for (i=0; i<strlen(label); i++) {
    if (label[i] != '"') {
      lbl1[p] = label[i];
      if (lbl1[p] >= 'f' && lbl1[p] <= 'z') lbl1[p] -= 32;
      p++;
      }
    }
  lbl1[p] = 0;
printf("searching: %s\n",lbl1);
  addr = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  addr = FromPtr(addr) + 2;
  flag = -1;
  while (flag) {
printf("%02x %02x %02x  ",ram[addr], ram[addr-1], ram[addr-2]);
    if (ram[addr] >= 0xc0 && ram[addr] <= 0xcd && ram[addr-2] >= 0xf0) {
      for (i=1; i<(ram[addr-2] & 0xf); i++)
        lbl2[i-1] = ram[addr-3-i];
      lbl2[(ram[addr-2] & 0xf)-1] = 0;
printf("label <<%s>>  ",lbl2);
      if (strcmp(lbl1, lbl2) == 0) {
        return addr+1;
printf("YES\n");
        }
else printf("NO\n");
      }
else printf("END\n");
    dst = ((ram[addr] & 0x0f) << 8) | ram[addr-1];
    dst = ((dst & 0x1ff) * 7) + ((dst >> 9) & 0x7);
    if (dst == 0) flag = 0;
      else addr += dst - 1;
    }
  Message("NONEXISTENT");
  return 0;
  }

