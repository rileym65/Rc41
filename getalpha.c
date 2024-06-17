#include "header.h"

char* GetAlpha(char* buffer) {
  int m;
  int p;
  m = REG_P+2;
  while (m >= REG_M && ram[m] == 0x00) m--;
  p = 0;
  while (m >= REG_M) {
    if (ram[m] != 0x00) buffer[p++] = ram[m];
    m--;
    }
  buffer[p] = 0;
  return buffer;
  }

