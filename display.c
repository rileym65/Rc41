#include "header.h"

char* Display(char* buffer) {
  int i;
  int p;
  int e;
  NUMBER a;
  char tmp[2];
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
      if (ram[i] == 0x00) buffer[p++] = '_';
      else if (ram[i] == 0x00) buffer[p++] = 0xff;
//      else if (ram[i] < 32 || ram[i] > 0x7e) buffer[p++] = '#';
      else buffer[p++] = ram[i];
      i--;
      }
    buffer[p] = 0;
    }
  if (FlagSet(22)) {
    if (ram[REG_E+1] & 0x10) strcpy(buffer,"-");
      else strcpy(buffer," ");
    p = 0;
    tmp[1] = 0;
    while (p < 10) {
      if (p == (ram[REG_E+2] & 0x0f)) strcat(buffer,".");
      if (ram[REG_Q+6-p] != 0xff &&
          ram[REG_Q+6-p] != 11) {
        tmp[0] = '0' + ram[REG_Q+6-p];
        strcat(buffer, tmp);
        p++;
        }
      else {
        p = 10;
        }
      }
    if (ram[REG_P+5] == 11) {
      while (strlen(buffer) < 8) strcat(buffer," ");
      if (ram[REG_E+1] & 0x20) strcat(buffer,"-");
        else strcat(buffer," ");
      p = strlen(buffer);
      if (ram[REG_P+4] != 0xff) buffer[p++] = '0' + ram[REG_P+4];
      if (ram[REG_P+3] != 0xff) buffer[p++] = '0' + ram[REG_P+3];
      buffer[p] = 0;
      }

    }
  else {
    a = RecallNumber(R_X);
    if (FlagSet(22)) {
      e = (a.exponent[0] * 10) + a.exponent[1];
      if (a.esign) e = -e;
      e += ex;
      a.esign = (e >= 0) ? 0 : 9;
      if (e < 0) e = -e;
      a.exponent[0] = e / 10;
      a.exponent[1] = e % 10;
      }
    Format(a,buffer);
    }
  while (strlen(buffer) < 12) strcat(buffer," ");
  return buffer;
  }
