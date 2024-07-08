#include "header.h"

void Print(byte b) {
  printBuffer[printPosition++] = b;
  printBuffer[printPosition] = 0x00;
  if (printPosition >= 24) {
    printf("%s\n", printBuffer);
    printPosition = 0;
    printBuffer[0] = 0;
    }
  }

void DecodeInstruction(byte b1, byte b2) {
  int i;
  if (b1 >= 0xa0 && b1 <= 0xa7) {
    i=0; 
    while (reverse2[i].cmd != 0xff &&
           (reverse2[i].cmd != b1 ||
            reverse2[i].post != b2)) i++;
    if (reverse2[i].cmd == 0xff) printf("UNKNOWN");
      else printf("%s", reverse2[i].name);
    return;
    }
  if (b1 < 0x10) {
    i=0;
    while (reverse[i].number != 0xff &&
           reverse[i].number != b2) i++;
    if (reverse[i].number == 0xff) printf("UNKNOWN");
      else printf("%s", reverse[i].name);
    return;
    }
  i=0;
  while (reverse[i].number != 0xff &&
         reverse[i].number != b1) i++;
  if (reverse[i].number == 0xff) printf("UNKNOWN");
    else printf("%s ", reverse[i].name);
  if (reverse[i].number == 0xff) return;
  if (b2 >= 0x80) printf("IND ");
  b2 &= 0x7f;
  if (b2 < 0x70) printf("%02d",b2);
  else
    switch (b2) {
      case 0x70: printf("T"); break;
      case 0x71: printf("Z"); break;
      case 0x72: printf("Y"); break;
      case 0x73: printf("X"); break;
      case 0x74: printf("L"); break;
      case 0x75: printf("M"); break;
      case 0x76: printf("N"); break;
      case 0x77: printf("O"); break;
      case 0x78: printf("P"); break;
      case 0x79: printf("Q"); break;
      case 0x7a: printf("|-"); break;
      case 0x7b: printf("a"); break;
      case 0x7c: printf("b"); break;
      case 0x7d: printf("c"); break;
      case 0x7e: printf("d"); break;
      case 0x7f: printf("e"); break;
      }
  }

void Printer(byte function) {
  int    addr;
  int    end;
  int    i;
  int    m;
  int    n;
  int    p;
  int    f;
  int    s;
  int    e;
  int    c;
  int    reg;
  int    r00;
  int    r[6];
  NUMBER x;
  char   buffer[256];
  if (FlagSet(55) == 0) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  if (FlagSet(21) == 0) return;

  if (function == 1) {                           // ACA
    n = 0;
    m = REG_P + 2;
    while (m >= REG_M) {
      if (ram[m] == 0 && n) buffer[p++] = '_';
      else if (ram[m] == 0) ;
      else if (ram[m] < ' ' || ram[m] > 0x7e) Print('#');
      else if (ram[m] >= 'f' && ram[m] <= 'z' && FlagSet(13) == 0)
        Print(ram[m] - 32);
      else if (ram[m] >= 'F' && ram[m] <= 'Z' && FlagSet(13) != 0)
        Print(ram[m] + 32);
      else Print(ram[m]);
      if (ram[m] != 0) n = -1;
      m--;
      }
    }

  else if (function == 2) {                      // ACCHR
    x = RecallNumber(R_X);
    if (x.esign >= 0) {
      m = x.mantissa[0];
      for (n=0; n<((x.exponent[0] * 10) + x.exponent[1]); n++) {
        if (n+1 < 10) m = (m * 10) + x.mantissa[n+1];
          else m *= 10;
        }
      if (m > 127) {
        Message("NONEXISTENT");
        Error();
        return;
        }
      }
    else m = 0;
    Print(m);
    }

  else if (function == 3) {                      // ACCOL
    x = RecallNumber(R_X);
    if (x.esign >= 0) {
      m = x.mantissa[0];
      for (n=0; n<((x.exponent[0] * 10) + x.exponent[1]); n++) {
        if (n+1 < 10) m = (m * 10) + x.mantissa[n+1];
          else m *= 10;
        }
      if (m > 127) {
        Message("DATA ERROR");
        Error();
        return;
        }
      }
    else m = 0;
    Print(m | 0x80);
    }

  else if (function == 4) {                      // ACSPEC
    r[6] = ((ram[REG_X+6] & 0x01) << 6) | ((ram[REG_X+5] & 0xfc) >> 2);
    r[5] = ((ram[REG_X+5] & 0x03) << 5) | ((ram[REG_X+4] & 0xf8) >> 3);
    r[4] = ((ram[REG_X+4] & 0x07) << 4) | ((ram[REG_X+3] & 0xf0) >> 4);
    r[3] = ((ram[REG_X+3] & 0x0f) << 3) | ((ram[REG_X+2] & 0xe0) >> 5);
    r[2] = ((ram[REG_X+2] & 0x1f) << 2) | ((ram[REG_X+1] & 0xc0) >> 6);
    r[1] = ((ram[REG_X+1] & 0x3f) << 1) | ((ram[REG_X+0] & 0x80) >> 7);
    r[0] = ram[REG_X+0] & 0x7f;
    for (i=6; i>=0; i--)
      Print(r[i] | 0x80);
    }

  else if (function == 5) {                      // ACX
    x = RecallNumber(R_X);
    Format(x, buffer);
    for (n=0; n<strlen(buffer); n++) {
      Print(buffer[n]);
      }
    }

  else if (function == 6) {                      // BLDSPEC
    ram[LIFT] = 'D';
    ram[PENDING] = 'E';
    x = RecallNumber(R_X);
    if (x.esign >= 0) {
      p = x.mantissa[0];
      for (n=0; n<((x.exponent[0] * 10) + x.exponent[1]); n++) {
        if (n+1 < 10) p = (p * 10) + x.mantissa[n+1];
          else p *= 10;
        }
      if (p > 127) {
        Message("DATA ERROR");
        Error();
        return;
        }
      }
    else {
      Message("DATA ERROR");
      Error();
      return;
      }
    if ((ram[REG_Y+6] & 0xf0) != 0x10) {
      for (i=REG_Y; i<REG_Y+6; i++) ram[i] = 0x00;
      ram[REG_Y+6] = 0x10;
      }
    r[5] = ((ram[REG_Y+5] & 0x03) << 5) | ((ram[REG_Y+4] & 0xf8) >> 3);
    r[4] = ((ram[REG_Y+4] & 0x07) << 4) | ((ram[REG_Y+3] & 0xf0) >> 4);
    r[3] = ((ram[REG_Y+3] & 0x0f) << 3) | ((ram[REG_Y+2] & 0xe0) >> 5);
    r[2] = ((ram[REG_Y+2] & 0x1f) << 2) | ((ram[REG_Y+1] & 0xc0) >> 6);
    r[1] = ((ram[REG_Y+1] & 0x3f) << 1) | ((ram[REG_Y+0] & 0x80) >> 7);
    r[0] = ram[REG_Y+0] & 0x7f;
    ram[REG_Y+6] = 0x10 | ((r[5] & 0x40) >> 6);
    ram[REG_Y+5] = ((r[5] & 0x3f) << 2) | ((r[4] >> 5) & 0x03);
    ram[REG_Y+4] = ((r[4] & 0x1f) << 3) | ((r[3] >> 4) & 0x07);
    ram[REG_Y+3] = ((r[3] & 0x0f) << 4) | ((r[2] >> 3) & 0x0f);
    ram[REG_Y+2] = ((r[2] & 0x07) << 5) | ((r[1] >> 2) & 0x1f);
    ram[REG_Y+1] = ((r[1] & 0x03) << 6) | ((r[0] >> 1) & 0x3f);
    ram[REG_Y+0] = ((r[0] & 0x01) << 7) | (p & 0x7f);
    x = RecallNumber(R_Y); StoreNumber(x, R_X);
    x = RecallNumber(R_Z); StoreNumber(x, R_Y);
    x = RecallNumber(R_T); StoreNumber(x, R_Z);
    }

  else if (function == 8) {                      // PRA
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    n = 0;
    p = 0;
    m = REG_P + 2;
    while (m >= REG_M) {
      if (ram[m] == 0 && n) buffer[p++] = '_';
      else if (ram[m] == 0) ;
      else if (ram[m] < ' ' || ram[m] > 0x7e) buffer[p++] = '#';
      else buffer[p++] = ram[m];
      if (ram[m] != 0) n = -1;
      m--;
      }
    buffer[p] = 0;
    printf("%s\n",buffer);
    }

  else if (function == 10) {                     // PRBUF
    printf("%s\n",printBuffer);
    strcpy(printBuffer,"");
    printPosition = 0;
    }

  else if (function == 11) {                     // PRFLAGS
    printf("\n");
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    printf("STATUS:\n");
    reg = (ram[REG_C+2] << 4) + ((ram[REG_C+1] >> 4) & 0x0f);
    printf("SIZE= %03d\n",RAMTOP - reg);
    reg = (ram[REG_C+6] << 4) | ((ram[REG_C+5] >> 4) & 0x0f);
    printf("E= %03d\n",reg);
    if (FlagSet(42) == 0 && FlagSet(43) == 0) printf("DEG\n");
    if (FlagSet(42) != 0 && FlagSet(43) == 0) printf("GRAD\n");
    if (FlagSet(42) == 0 && FlagSet(43) != 0) printf("RAD\n");
    n = 0;
    if (FlagSet(36)) n |= 8;
    if (FlagSet(37)) n |= 4;
    if (FlagSet(38)) n |= 2;
    if (FlagSet(39)) n |= 1;
    if (FlagSet(40) == 0 && FlagSet(41) == 0) printf("SCI %d\n",n);
    if (FlagSet(40) != 0 && FlagSet(41) == 0) printf("FIX %d\n",n);
    if (FlagSet(40) == 0 && FlagSet(41) != 0) printf("ENG %d\n",n);
    printf("\n");
    printf("FLAGS:\n");
    m = REG_D+6;
    f = 0;
    while (m >= REG_D) {
      p = ram[m--];
      for (n=0; n<8; n++) {
        if (p & 0x80) printf("F %02d  SET\n",f);
          else printf("F %02d  CLEAR\n",f);
        p <<= 1;
        f++;
        }
      }
    }

  else if (function == 12) {                          // PRKEYS
    printf("\n");
    addr = 0x0c0 * 7;
    c = 0;
    while (ram[addr+6] == 0xf0) {
      if (ram[addr+0] != 0) {
        if (c == 0) printf("USER KEYS:\n");
        c++;
        if ((ram[addr+0] & 0x0f) >= 0x01 && (ram[addr+0] & 0x0f) <= 0x08)
          printf(" %02x: ",ram[addr+0]);
        else
          printf("-%02x: ",ram[addr+0] & 0xf7);
        DecodeInstruction(ram[addr+2], ram[addr+1]);
        printf("\n");
        }
      if (ram[addr+3] != 0) {
        if (c == 0) printf("USER KEYS:\n");
        c++;
        if ((ram[addr+3] & 0x0f) >= 0x01 && (ram[addr+3] & 0x0f) <= 0x08)
          printf(" %02x: ",ram[addr+3]);
        else
          printf("-%02x: ",ram[addr+3] & 0xf7);
        DecodeInstruction(ram[addr+5], ram[addr+4]);
        printf("\n");
        }
      addr += 7;
      }
    addr = (ram[REG_C+2] << 4) | ((ram[REG_C+1] & 0xf0) >> 4);
    addr = (addr * 7) - 1;
    while (ram[addr] < 0xc0 || ram[addr] >= 0xce || (ram[addr-2] & 0xf0) != 0x20) {
      if (ram[addr] >= 0xc0 && ram[addr] < 0xce) {
        if (ram[addr-2] >= 0xf0) {
          if (ram[addr-3] != 0x00) {
            if (c == 0) printf("USER KEYS:\n");
            c++;
            if ((ram[addr-3] & 0x0f) <= 0x08) printf(" %02x: \"",ram[addr-3]);
              else printf("-%02x: \"",ram[addr-3] & 0xf7);
            for (i=1; i<(ram[addr-2]&0x0f); i++)
              if (ram[addr-3-i] == 0) printf("_");
                else printf("%c",ram[addr-3-i]);
            printf("\n");
            }
          }
        }
      addr -= isize(addr);
      }
    end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
    if (c == 0) printf("USER KEYS:NONE\n");

    }

  else if (function == 16) {                          // PRREG
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    n = 0;
    reg = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    while (reg < RAMTOP) {
      x = RecallNumber(reg);
      Format(x, buffer);
      printf("R%02d= %s\n",n,buffer);
      n++;
      reg++;
      }
    }

  else if (function == 17) {                          // PRREGX
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    x = RecallNumber(R_X);
    s = 0;
    e = 0;
    p = 0;
    if (x.esign == 0) {
      s = x.mantissa[p++];
      n = x.exponent[0] * 10 + x.exponent[1];
      while (n > 0) {
        s *= 10;
        if (p < 10) s += x.mantissa[p++];
        n--;
        }
      }
    else {
      n = x.exponent[0] * 10 + x.exponent[1];
      while (n > 0) {
        n--;
        p--;
        }
      p++;
      }
    for (i=0; i<3; i++) {
      e *= 10;
      if (p >= 0 && p < 10) e += x.mantissa[p];
      p++;
      }
    reg = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    n = s;
    e += reg;
    reg += s;
    if (reg > 0xfff) {
      Message("NONEXISTENT");
      Error();
      }
    else {
      while (reg <= e) {
        if (reg > 0xfff) {
          Message("NONEXISTENT");
          Error();
          reg = e+1;
          }
        else {
          x = RecallNumber(reg);
          Format(x, buffer);
          printf("R%02d= %s\n",n,buffer);
          n++;
          reg++;
          }
        }
      }
    }

  else if (function == 18) {                          // PRE
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    reg = (ram[REG_C+6] << 4) | ((ram[REG_C+5] >> 4) & 0x0f);
    r00 = ((ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f));
    x = RecallNumber(reg+r00);
    Format(x, buffer);
    printf("EX  = %s\n",buffer);
    x = RecallNumber(reg+r00+1);
    Format(x, buffer);
    printf("EX^2= %s\n",buffer);
    x = RecallNumber(reg+r00+2);
    Format(x, buffer);
    printf("EY  = %s\n",buffer);
    x = RecallNumber(reg+r00+3);
    Format(x, buffer);
    printf("EY^2= %s\n",buffer);
    x = RecallNumber(reg+r00+4);
    Format(x, buffer);
    printf("EXY = %s\n",buffer);
    x = RecallNumber(reg+r00+5);
    Format(x, buffer);
    printf("N   = %s\n",buffer);
    }

  else if (function == 19) {                          // PRSTK
    printf("\n");
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    x = RecallNumber(R_T);
    Format(x, buffer);
    printf("T= %s\n",buffer);
    x = RecallNumber(R_Z);
    Format(x, buffer);
    printf("Z= %s\n",buffer);
    x = RecallNumber(R_Y);
    Format(x, buffer);
    printf("Y= %s\n",buffer);
    x = RecallNumber(R_X);
    Format(x, buffer);
    printf("X= %s\n",buffer);
    }

  else if (function == 20) {                          // PRX
    if (printPosition != 0) {
      printf("%s\n",printBuffer);
      printBuffer[0] = 0;
      printPosition = 0;
      }
    x = RecallNumber(R_X);
    Format(x, buffer);
    printf("%s\n",buffer);
    }

  else if (function == 22) {                          // SKPCHR
    x = RecallNumber(R_X);
    if (x.esign >= 0) {
      m = x.mantissa[0];
      for (n=0; n<((x.exponent[0] * 10) + x.exponent[1]); n++) {
        if (n+1 < 10) m = (m * 10) + x.mantissa[n+1];
          else m *= 10;
        }
      if (m > 127) {
        Message("NONEXISTENT");
        Error();
        return;
        }
      }
    else m = 0;
    for (i=0; i<m; i++)
      Print(' ');
    }

  else if (function == 23) {                          // SKPCOL
    x = RecallNumber(R_X);
    if (x.esign >= 0) {
      m = x.mantissa[0];
      for (n=0; n<((x.exponent[0] * 10) + x.exponent[1]); n++) {
        if (n+1 < 10) m = (m * 10) + x.mantissa[n+1];
          else m *= 10;
        }
      if (m > 127) {
        Message("NONEXISTENT");
        Error();
        return;
        }
      }
    else m = 0;
    for (i=0; i<m; i++)
      Print(0x80);
    }
  else {
    Message("NONEXISTENT");
    Error();
    }
  }

