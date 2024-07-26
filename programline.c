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
    if (b < 100) {
      sprintf(tmp,"%02d",b);
      strcat(buffer,tmp);
      }
    if (b >= 102 && b <= 111) {
      tmp[0] = b - 102 + 'A';
      tmp[1] = 0;
      strcat(buffer,tmp);
      }
    if (b == 122) {
      tmp[0] = 122;
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
  else if (b == 122) {
    tmp[0] = 122;
    tmp[1] = 0;
    strcat(buffer,tmp);
    }
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
  return buffer;
  }

int ProgramNumber(int adr, char* buffer) {
  int  b;
  int  p;
  char mode;
  char mant[32];
  char expn[32];
  char sign;
  char esign;
  mode = 'M';
  p = 0;
  sign = ' ';
  esign = ' ';
  while (ram[adr] >= 0x10 && ram[adr] <= 0x1c) adr++;
  adr--;
  b = ram[adr];
  while (b >= 0x10 && b <= 0x1c) {
    if (b <= 0x19) {
      if (mode == 'M') mant[p++] = '0' + b - 0x10;
        else expn[p++] = '0'+ b - 0x10;
      }
    if (b == 0x1a) mant[p++] = '.';
    if (b == 0x1b) {
      if (mode == 'M') {
        mant[p] = 0;
        p = 0;
        mode = 'E';
        }
      }
    if (b == 0x1c) {
      if (mode == 'M') sign = (sign == ' ') ? '-' : ' ';
        else esign = (esign == ' ') ? '-' : ' ';
      }
    adr--;
    b = ram[adr];
    }
  if (mode == 'M') mant[p] = 0;
  if (sign == '-') strcat(buffer,"-");
  strcat(buffer, mant);
  if (mode == 'E') {
    expn[p] = 0;
    strcat(buffer," E");
    if (esign == '-') strcat(buffer,"-");
    strcat(buffer,expn);
    }
  return adr;
  }

char* ProgramList(int lineNumber, int adr, char* buffer) {
  int i;
  int b;
  int b2;
  int end;
  char tmp[256];
  strcpy(buffer,"");
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
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
        strcat(buffer,"LBL");
        tmp[0] = 0x60;
        tmp[1] = 0x00;
        strcat(buffer, tmp);
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
      if (b >= 0x10 && b <= 0x1c) {
        adr = ProgramNumber(adr, buffer);
        }
      else if (b == 0xae) {
        b2 = ram[adr-1];
        if (b2 >= 0x80) {
          sprintf(buffer,"%02d XEQ IND %02d",lineNumber, b2 & 0x7f);
          }
        else {
          sprintf(buffer,"%02d GTO IND %02d",lineNumber, b2 & 0x7f);
          }
        }
      else if (b >= 0xa0 && b <= 0xa7) {
        b2 = ram[adr-1];
        i = 0;
        while (reverse2[i].cmd != 0xff && (reverse2[i].cmd != b || reverse2[i].post != b2)) i++;
        if (reverse2[i].cmd != 0xff) {
          sprintf(buffer,"%02d %s",lineNumber, reverse2[i].name);
          }
        else {
          b = ((b & 0x0f) << 2) | ((b2 & 0xc0) >> 6);
          b2 &= 0x3f;
          sprintf(buffer,"%02d XROM %02d,%02d",lineNumber,b,b2);
          }
        }
      else if (b < 0xf0 && (reverse[b].size & 0x0f) == 1) {
        sprintf(tmp, "%s", reverse[b].name);
        strcat(buffer, tmp);
        }
      else if (b < 0xf0 && (reverse[b].size & 0x0f) == 2) {
        Postfix(b, adr, buffer);
        }
      else if ((reverse[b].size & 0xf0) == 0x60) {
        if (ram[adr-2] >= 102 && ram[adr-2] <= 111)
          sprintf(tmp, "%s %c", reverse[b].name, ram[adr-2] - 102 + 'A');
        else if (ram[adr-2] >= 123 && ram[adr-2] <= 127)
          sprintf(tmp, "%s %c", reverse[b].name, ram[adr-2] - 123 + 'a');
        else
          sprintf(tmp, "%s %02d", reverse[b].name, ram[adr-2] & 0x7f);
        strcat(buffer, tmp);
        }
      else if ((reverse[b].size & 0xf0) == 0x10) {
        sprintf(tmp, "%s", reverse[b].name);
        strcat(buffer, tmp);
        b = ram[--adr] & 0x0f;
        tmp[0] = 0x60;
        tmp[1] = 0x00;
        strcat(buffer, tmp);
        for (i=0; i<b; i++) {
          tmp[0] = ram[--adr];
          tmp[1] = 0;
          strcat(buffer,tmp);
          }
        }
      else if (b >= 0xf0) {
        adr--;
        buffer[strlen(buffer)-1] = 0x60;
        tmp[1] = 0;
        for (i=0; i<(b&0x0f); i++) {
          if (ram[adr] == 0x7f) { tmp[0] = 0x7f; adr--; }
          else if (ram[adr] == 0x00) { tmp[0] = 0xff; adr--; }
          else if (ram[adr] > 0x7f) {
            tmp[0] = '*'; adr--;
            }
            else tmp[0] = ram[adr--];
          strcat(buffer, tmp);
          }
        }
      else
sprintf(buffer, "b=%02x, size=%d",b,reverse[b].size);
      }
  return buffer;
  }

char* ProgramLine(char* buffer) {
  int addr;
  int reg;
  int byt;
  int adr;
  int lineNumber;
  int end;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  lineNumber = ram[REG_E+0] + ((ram[REG_E+1] &0x0f) << 8);
  if (lineNumber == 0xfff) {
    FixLineNumber();
    lineNumber = ram[REG_E+0] + ((ram[REG_E+1] &0x0f) << 8);
    }
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  if (lineNumber == 0) {
    sprintf(buffer,"00 REG %d", end - 0x0c0);
    }
  else {
    adr--;
    ProgramList(lineNumber, adr, buffer);
    }

  return buffer;
  }

