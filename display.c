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
    while (i >= REG_M) {
printf("Print alpha\n");
      if (ram[i] == 0x00) buffer[p++] = '_';
      else if (ram[i] < 32 || ram[i] > 0x7e) buffer[p++] = '#';
      else buffer[p++] = ram[i];
      i--;
      }
    buffer[p] = 0;
    }
  else {
    a = RecallNumber(R_X);
    Format(a,buffer);
    }
  while (strlen(buffer) < 12) strcat(buffer," ");
  return buffer;
  }
