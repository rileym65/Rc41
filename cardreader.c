#include "header.h"
#include <fcntl.h>

int CardReader(byte function, int addr) {
  int s;
  int e;
  int n;
  int i;
  int flag;
  int r00;
  int file;
  int len;
  int p;
  char card[5];
  NUMBER a;
  NUMBER b;
  NUMBER x;
  char   filename[1024];

  if (function == 2) {                           // RDTA
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    file = open(filename, O_RDONLY, 0666);
    if (file >= 0) {
      len = RAMTOP - r00;
      r00 *= 7;
      read(file, card, 5);
      if (card[0] != 'D') {
        Message("CARD ERR");
        }
      else {
        read(file, ram+r00, len);
        }
      close(file);
      }
    }

  if (function == 3) {                           // RDTAX
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
    r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    len = 1+e-s;
    s += r00;
    e += r00;
    s *= 7;
    e *= 7;
    len *= 7;
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    file = open(filename, O_RDONLY, 0666);
    if (file >= 0) {
      read(file, card, 5);
      if (card[0] != 'D') {
        Message("CARD ERR");
        }
      else {
        read(file, ram+s, len);
        }
      close(file);
      }
    }

  if (function == 5) {                           // RDTA
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    file = open(filename, O_RDONLY);
    if (file >= 0) {
      read(file, card, 5);
      sprintf(filename,"TYPE %c TR 01",card[0]);
      Message(filename);
      close(file);
      }
    }

  if (function == 6) {                           // WALL
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (file >= 0) {
      len = RAMTOP;
      r00 *= 7;
      card[0] = 'A';
      card[1] = 0x00;
      card[2] = 0x01;
      i = ((len+15) / 16);
      card[3] = (i >> 8) & 0xff;
      card[4] = i & 0xff;
      len *= 7;
      write(file, card, 5);
      write(file, ram, len);
      close(file);
      }
    }

  if (function == 7) {                           // WDTA
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (file >= 0) {
      len = RAMTOP - r00;
      r00 *= 7;
      card[0] = 'D';
      card[1] = 0x00;
      card[2] = 0x01;
      i = ((len+15) / 16);
      card[3] = (i >> 8) & 0xff;
      card[4] = i & 0xff;
      len *= 7;
      write(file, card, 5);
      write(file, ram+r00, len);
      close(file);
      }
    }

  if (function == 8) {                           // WDTAX
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
    r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
    len = 1+e-s;
    s += r00;
    e += r00;
    s *= 7;
    e *= 7;
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (file >= 0) {
      card[0] = 'D';
      card[1] = 0x00;
      card[2] = 0x01;
      i = ((len+15) / 16);
      card[3] = (i >> 8) & 0xff;
      card[4] = i & 0xff;
      len *= 7;
      write(file, card, 5);
      write(file, ram+s, len);
      close(file);
      }
    }

  if (function == 11) {                          // 7CLREG
    for (i=0; i<10; i++) Sto(ZERO, i);
    for (i=20; i<=25; i++) Sto(ZERO, i);
    }

  if (function == 12) {                          // 7DSP0
    ClearFlag(36);
    ClearFlag(37);
    ClearFlag(38);
    ClearFlag(39);
    }

  if (function == 13) {                          // 7DSP1
    ClearFlag(36);
    ClearFlag(37);
    ClearFlag(38);
    SetFlag(39);
    }

  if (function == 14) {                          // 7DSP2
    ClearFlag(36);
    ClearFlag(37);
    SetFlag(38);
    ClearFlag(39);
    }

  if (function == 15) {                          // 7DSP3
    ClearFlag(36);
    ClearFlag(37);
    SetFlag(38);
    SetFlag(39);
    }

  if (function == 16) {                          // 7DSP4
    ClearFlag(36);
    SetFlag(37);
    ClearFlag(38);
    ClearFlag(39);
    }

  if (function == 17) {                          // 7DSP5
    ClearFlag(36);
    SetFlag(37);
    ClearFlag(38);
    SetFlag(39);
    }

  if (function == 18) {                          // 7DSP6
    ClearFlag(36);
    SetFlag(37);
    SetFlag(38);
    ClearFlag(39);
    }

  if (function == 19) {                          // 7DSP7
    ClearFlag(36);
    SetFlag(37);
    SetFlag(38);
    SetFlag(39);
    }

  if (function == 20) {                          // 7DSP8
    SetFlag(36);
    ClearFlag(37);
    ClearFlag(38);
    ClearFlag(39);
    }

  if (function == 21) {                          // 7DSP9
    SetFlag(36);
    ClearFlag(37);
    ClearFlag(38);
    SetFlag(39);
    }

  if (function == 22) {                          // 7DSPI
    a = Rcl(25);
    i = ToInteger(a);
    if (i < 0 || i > 9 || a.sign) {
      Message("DATA ERROR");
      Error();
      }
    else {
      if (i & 8) SetFlag(36); else ClearFlag(36);
      if (i & 4) SetFlag(37); else ClearFlag(37);
      if (i & 2) SetFlag(38); else ClearFlag(38);
      if (i & 1) SetFlag(39); else ClearFlag(39);
      }
    }

  if (function == 23) {                          // 7DSZ
    a = Rcl(25);
    a = Sub(a, ONE);
    Sto(a, 25);
    flag = 0;
    for (i=0; i<10; i++)
      if (a.mantissa[i] != 0) flag = -1;
    if (flag == 0 && addr >= 0x0c0) addr =Skip(addr);
    }

  if (function == 24) {                          // 7DSZI
    a = Rcl(25);
    i = ToInteger(a);
    if (i < 0 || i > 25 || a.sign) {
      Message("DATA ERROR");
      Error();
      }
    else {
      a = Rcl(i);
      a = Sub(a, ONE);
      Sto(a, i);
      flag = 0;
      for (i=0; i<10; i++)
        if (a.mantissa[i] != 0) flag = -1;
      if (flag == 0 && addr >= 0x0c0) addr =Skip(addr);
      }
    }

  if (function == 25) {                          // 7ENG
    ClearFlag(40);
    SetFlag(41);
    }

  if (function == 26) {                          // 7FIX
    SetFlag(40);
    ClearFlag(41);
    }

  if (function == 29) {                          // 7ISZ
    a = Rcl(25);
    a = Add(a, ONE);
    Sto(a, 25);
    flag = 0;
    for (i=0; i<10; i++)
      if (a.mantissa[i] != 0) flag = -1;
    if (flag == 0) addr =Skip(addr);
    }

  if (function == 30) {                          // 7ISZI
    a = Rcl(25);
    i = ToInteger(a);
    if (i < 0 || i > 25 || a.sign) {
      Message("DATA ERROR");
      Error();
      }
    else {
      a = Rcl(i);
      a = Add(a, ONE);
      Sto(a, i);
      flag = 0;
      for (i=0; i<10; i++)
        if (a.mantissa[i] != 0) flag = -1;
      if (flag == 0 && addr >= 0x0c0) addr =Skip(addr);
      }
    }

  if (function == 31) {                          // 7P<>S
    for (i=0; i<10; i++) {
      a = Rcl(i);
      b = Rcl(i+10);
      Sto(a, i+10);
      Sto(b, i);
      }
    }

  if (function == 36) {                          // 7SCI
    ClearFlag(40);
    ClearFlag(41);
    }

  if (function == 37) {                          // RALL
    printf("Card file? ");
    fgets(filename, 1023, stdin);
    while (strlen(filename) > 0 && filename[strlen(filename)-1] < ' ')
      filename[strlen(filename)-1] = 0;
    file = open(filename, O_RDONLY);
    if (file >= 0) {
      len = RAMTOP;
      len *= 7;
      read(file, card, 5);
      if (card[0] != 'A') {
        Message("CARD ERR");
        }
      else {
        read(file, ram, len);
        }
      close(file);
      }
    }

  return addr;
  }

