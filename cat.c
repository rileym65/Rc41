#include "header.h"

void Cat(char* token) {
  int addr;
  int i;
  int end;
  printf("\n");
  if (strcmp(token, "1") == 0) {
    addr = (ram[REG_C+2] << 4) | ((ram[REG_C+1] & 0xf0) >> 4);
    addr = (addr * 7) - 1;
    while (ram[addr] < 0xc0 || ram[addr] >= 0xce || (ram[addr-2] & 0xf0) != 0x20) {
      if (ram[addr] >= 0xc0 && ram[addr] < 0xce) {
        if (ram[addr-2] >= 0xf0) {
          printf("LBL\"");
          for (i=1; i<(ram[addr-2]&0x0f); i++)
            if (ram[addr-3-i] == 0) printf("_");
              else printf("%c",ram[addr-3-i]);
          printf("\n");
          }
        else printf("END\n");
        }
      addr -= isize(addr);
      }
    end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
    printf(".END. REG %d\n",end - 0x0c0);
    }
  if (strcmp(token, "2") == 0) {
    i = 0;
    while (catalog2[i].flags != 0xff) {
      printf("%s\n",catalog2[i++].name);
      }
    }
  if (strcmp(token, "3") == 0) {
    i = 12;
    while (catalog[i].flags != 0xff) {
      printf("%s\n",catalog[i++].name);
      }
    }
  }

