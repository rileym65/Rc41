#include "header.h"

char* Postfix(byte i, int adr, char* buffer) {
  byte b;
  char tmp[256];
  sprintf(tmp, "%s ", reverse[i].name);
  strcat(buffer, tmp);
  adr--;
  b = ram[adr];
  if (b >= 0x80) strcat(buffer,"IND ");
  b &= 0x7f;
  if (b == 112) strcat(buffer,"T");
  else if (b == 113) strcat(buffer,"Z");
  else if (b == 114) strcat(buffer,"Y");
  else if (b == 115) strcat(buffer,"X");
  else if (b == 116) strcat(buffer,"L");
  else if (b == 117) strcat(buffer,"M");
  else if (b == 118) strcat(buffer,"N");
  else if (b == 119) strcat(buffer,"O");
  else if (b == 120) strcat(buffer,"P");
  else if (b == 121) strcat(buffer,"Q");
  else if (b == 122) strcat(buffer,"|-");
  else if (b == 123) strcat(buffer,"a");
  else if (b == 124) strcat(buffer,"b");
  else if (b == 125) strcat(buffer,"c");
  else if (b == 126) strcat(buffer,"d");
  else if (b == 127) strcat(buffer,"e");
  else {
    if ((reverse[i].size & 0xf0) == 0x80) {
      if (b < 65) {
        sprintf(tmp, "%d", b % 10);
        strcat(buffer, tmp);
        }
      else {
        sprintf(tmp, "%c", b);
        }
      }
    else {
      sprintf(tmp, "%02d", b);
      strcat(buffer, tmp);
      }
    }
  }

char* ProgramLine(char* buffer) {
  int addr;
  int reg;
  int byt;
  int b;
  int adr;
  int lineNumber;
  int end;
  char tmp[256];
  addr = (ram[REG_B*7+1] << 8) | ram[REG_B*7+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  lineNumber = ram[REG_E*7+0] + ((ram[REG_E*7+1] &0x0f) << 8);
  end = ((ram[REG_C*7+1] & 0x0f) << 8) | ram[REG_C*7+0];
  if (lineNumber == 0) {
    sprintf(buffer,"00 REG %d", end - 0x0c0);
    }
  else {
    adr--;
    while (ram[adr] == 0) adr--;
    if (lineNumber < 100) sprintf(buffer, "%02d ", lineNumber);
      else sprintf(buffer,"%d ", lineNumber);
    
    b = ram[adr];
    if (b >= 0xc0 && b < 0xce) {
      if (ram[adr-2] < 0xf0) {
        if ((ram[adr] & 0x0f) == 0 || (ram[adr-1] == 0)) {
          sprintf(buffer,".END. REG %d", end - 0x0c0);
          }
        else{
strcpy(buffer,"END");
          }
        }
      else {
strcpy(buffer,"Alpha text");
        }
      }
    else {
      if ((reverse[b].size & 0x0f) == 1) {
        sprintf(tmp, "%s", reverse[b].name);
        strcat(buffer, tmp);
        }
      else if ((reverse[b].size & 0x0f) == 2) {
        Postfix(b, adr, buffer);
        }
      else
sprintf(buffer, "b=%02x, size=%d",b,reverse[b].size);
      }
    }


  }

