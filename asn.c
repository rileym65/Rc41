#include "header.h"

void Asn(char* command, char* key) {
  int  i;
  int  flag;
  int  entry;
  int  cat;
  int  ky;
  int  addr;
  int  b1;
  int  b2;
  char cmd[32];
  if (command[0] != '"' || command[strlen(command)-1] != '"') {
    Message("NONEXISTENT");
    Error();
    return;
    }
  strcpy(cmd, command+1);
  cmd[strlen(cmd)-1] = 0;
  entry = 0;
  flag = -1;
  cat = 0;
  while (flag) {
    if (strcasecmp(cmd, catalog[entry].name) == 0) flag = 0;
      else if (catalog[++entry].flags == 0xff) flag = 0;
    }
  if (catalog[entry].flags != 0xff) {
    cat = 1;
    b1 = 0x04;
    b2 = catalog[entry].cmd;
    }
  if (cat == 0) {
    entry = 0;
    flag = -1;
    while (flag) {
      if (strcasecmp(cmd, catalog2[entry].name) == 0) flag = 0;
        else if (catalog2[++entry].flags == 0xff) flag = 0;
      }
    if (catalog2[entry].flags != 0xff) {
      cat = 2;
      b1 = catalog2[entry].cmd;
      b2 = catalog2[entry].post;
      }
    }
  if (cat == 0) {
    addr = FindGlobal(cmd);
    if (addr != 0) {
       addr--;
       cat = 3;
       }
    }
  if (cat == 0) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  ky =0;
  flag = -1;
  while (flag) {
    if (strcasecmp(key, keys[ky].key) == 0) flag = 0;
      else if (keys[++ky].keycode == 0xff) flag = 0;
    }
  if (keys[ky].keycode == 0xff) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  UnAsn(keys[ky].keycode, 3);
  if (cat == 3) {
    ram[addr-3] = keys[ky].keycode;
    SetKaFlag(keys[ky].keycode, 1);
    return;
    }
  addr = 0x0c0 * 7;
  flag =-1;
  while (flag) {
    if (ram[addr+6] != 0xf0) flag = 0;
    if (ram[addr+5] == 0x00) flag = 0;
    if (ram[addr+2] == 0x00) flag = 0;
    if (flag) addr += 7;
    }
  if (ram[addr+6] != 0xf0) {
    for (i=0; i<6; i++) ram[addr+i] = 0x00;
    ram[addr+6] = 0xf0;
    }
  if (ram[addr+2] == 0x00) {
    ram[addr+2] = b1;
    ram[addr+1] = b2;
    ram[addr+0] = keys[ky].keycode;
    }
  else {
    ram[addr+5] = b1;
    ram[addr+4] = b2;
    ram[addr+3] = keys[ky].keycode;
    }  
  SetKaFlag(keys[ky].keycode, 1);
  }

