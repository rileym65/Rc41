#include "header.h"

char* Display(char* buffer) {
  int i;
  int p;
  NUMBER a;
  if (FlagSet(52)) {
    ProgramLine(buffer);
    }
  else if (FlagSet(50)) {
    strcpy(buffer, display);
    }
  else if (FlagSet(48)) {
    i = REG_P + 2;
    while (ram[i] == 0x00 && i >= REG_M) i--;
    p = 0;
    while (i >= REG_M) buffer[p++] = ram[i--];
    buffer[p] = 0;
    }
  else {
    a = RecallNumber(R_X);
    Format(a,buffer);
    }
  while (strlen(buffer) < 12) strcat(buffer," ");
  return buffer;
  }
