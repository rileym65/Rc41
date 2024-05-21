#include "header.h"

char* Postfix(byte i, int adr, char* buffer) {
  byte b;
  char tmp[256];
  sprintf(tmp, "%s ", reverse[i].name);
  strcat(buffer, tmp);
  if ((reverse[i].size & 0xf0) == 0x40) return buffer;
  adr--;
  b = ram[adr];
  if (b >= 0x80) strcat(buffer,"IND ");
  b &= 0x7f;
  if ((reverse[i].size & 0xf0) == 0x90) {
    if (b >= 102 && b <= 111) {
      tmp[0] = b - 102 + 'A';
      tmp[1] = 0;
      strcat(buffer,tmp);
      }
    if (b >= 123 && b <= 127) {
      tmp[0] = b - 123 + 'a';
      tmp[1] = 0;
      strcat(buffer,tmp);
      }
    }
  else if (b == 112) strcat(buffer,"T");
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
  int i;
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
        if ((ram[adr-2] & 0xf0) == 0x20) {
          sprintf(buffer,".END. REG %d", end - 0x0c0);
          }
        else{
          if (lineNumber < 100) sprintf(buffer, "%02d END", lineNumber);
            else sprintf(buffer,"%d END", lineNumber);
          }
        }
      else {
        if (lineNumber < 100) sprintf(buffer, "%02d ", lineNumber);
          else sprintf(buffer,"%d ", lineNumber);
        strcat(buffer,"LBL\"");
        adr -= 2;
        b = ram[adr] - 1;
        b &= 0xf;
        adr -= 2;
        for (i=0; i<b; i++) {
          if (ram[adr] == 0) tmp[0] = '_';
            else tmp[0] = ram[adr];
          adr--;
          tmp[1] = 0;
          strcat(buffer,tmp);
          }
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
      else if ((reverse[b].size & 0xf0) == 0x60) {
        if (ram[adr-2] >= 102 && ram[adr-2] <= 111)
          sprintf(tmp, "%s %c", reverse[b].name, ram[adr-2] - 102 + 'A');
        else if (ram[adr-2] >= 123 && ram[adr-2] <= 127)
          sprintf(tmp, "%s %c", reverse[b].name, ram[adr-2] - 123 + 'a');
        else
          sprintf(tmp, "%s %02d", reverse[b].name, ram[adr-2]);
        strcat(buffer, tmp);
        }
      else if ((reverse[b].size & 0xf0) == 0x10) {
        sprintf(tmp, "%s", reverse[b].name);
        strcat(buffer, tmp);
        b = ram[--adr] & 0x0f;
        strcat(buffer,"\"");
        for (i=0; i<b; i++) {
          tmp[0] = ram[--adr];
          tmp[1] = 0;
          strcat(buffer,tmp);
          }
        }
      else
sprintf(buffer, "b=%02x, size=%d",b,reverse[b].size);
      }
    }


  }

