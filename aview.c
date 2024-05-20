#include "header.h"

void Aview() {
  int n;
  int m;
  int p;
  char buffer[32];
  n = 0;
  m = REG_P * 7 + 2;
  while (m >= REG_M*7) {
    if (n) {
      if (ram[m] == 0) buffer[p++] = 0xff;
        else buffer[p++] = ram[m];
      }
    else if (ram[m] != 0) {
      n = -1;
      buffer[p++] = ram[m];
      }
    m--;
    }
  buffer[p] = 0;
  Message(buffer);
  }

