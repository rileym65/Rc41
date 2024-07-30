#include "header.h"

void Link(int address) {
  int adr;
  int reg;
  int byt;
  int next;
  int diff;
  int lnext;
  int prev;
  next = FindNextGlobal(address-1);
  lnext = ((ram[next] & 0x0f) << 8) | ram[next-1];
  if (lnext != 0) {
    prev = ((lnext & 0x1ff) * 7) + ((lnext >> 9) & 0x7) + next + byteCount - 1;
    }
  diff = 1 + address - next;
  reg = diff / 7;
  byt = diff % 7;
  adr = (byt << 9) | reg;
  ram[next] &= 0xf0;
  ram[next] |= ((adr >> 8) & 0x0f);
  ram[next-1] = adr & 0xff;
  if (lnext != 0) {
    diff = 1 + prev - address;
    reg = diff / 7;
    byt = diff % 7;
    adr = (byt << 9) | reg;
    ram[address] &= 0xf0;
    ram[address] |= ((adr >> 8) & 0x0f);
    ram[address-1] = adr & 0xff;
    }
  byteCount = 0;
  }

void ClearLinks(int address) {
  int pstart;
  int pend;
  if (linksCleared) return;
  linksCleared = -1;
  pend = FindEnd(address);
  pstart = FindStart(address);
  while (ram[pstart] == 0x00) pstart--;
  while (pstart > pend) {
    if ((ram[pstart] & 0xf0) == 0xb0) {
      ram[pstart-1] = 0;
      }
    if ((ram[pstart] & 0xf0) == 0xd0) {
      ram[pstart] &= 0xf0;
      ram[pstart-1] = 0;
      }
    if ((ram[pstart] & 0xf0) == 0xe0) {
      ram[pstart] &= 0xf0;
      ram[pstart-1] = 0;
      }
    pstart -= isize(pstart);
    }
  }

void ProgramStep(char* line) {
  int i;
  int addr;
  int gaddr;
  int adr;
  int byt;
  int reg;
  int start;
  int pend;
  int lineNumber;
  int greg;
  int gbyt;
  int l;
  int d;
  byteCount = 0;
//  if (ram[REG_R+1] == 0x00 && line == NULL) return;
  addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
  reg = (addr & 0xfff);
  byt = (addr >> 12) & 0xf;
  adr = (reg * 7) + byt;
  ClearLinks(adr);
  lineNumber = ram[REG_E+0] + ((ram[REG_E+1] &0x0f) << 8);
  if (lineNumber == 0) {
    adr--;
    }
  else {
    adr--;
    if (!FlagSet(22)) {
      while (ram[adr] == 0) adr--;
      if (ram[adr] < 0xc0 || ram[adr] > 0xcd || ram[adr-2] >= 0xf0) {
        adr -= isize(adr);
        }
      } 
    else adr--;
    }
  start = adr+1;
  pend = FindEnd(adr);
  ram[pend-2] |= 0x04;
  reg = adr / 7;
  byt = adr % 7;
  addr = (byt << 12) | reg;
  ram[REG_B+1] = (addr >> 8) & 0xff;
  ram[REG_B+0] = addr & 0xff;
  if (ram[REG_R+1] < 0x10 || ram[REG_R+1] > 0x1c) ClearFlag(22);
//  if (!FlagSet(22)) ProgramByte(ram[REG_R+1]);
  ProgramByte(ram[REG_R+1]);
  if (line != NULL) {
    if (line[0] == '.' || (line[0] >= '0' && line[0] <= '9')) {
      if (!FlagSet(22)) ProgramByte(0x00);
      SetFlag(22);
      for (i=0; i<strlen(line); i++) {
        if (line[i] == '.') ProgramByte(0x1a);
        else if (line[i] >= '0' && line[i] <= '9')
          ProgramByte(line[i] - 32);
        }
      }
    if (line[0] == '"') {
      ClearFlag(22);
      for (i=0; i<strlen(line); i++) {
        if (line[i] != '"') {
          if (line[i] > 'e' && line[i] <= 'z') ProgramByte(line[i]-32);
          else if (line[i] == '|') ProgramByte(0x7f);
          else ProgramByte(line[i]);
          ram[start-1]++;
          }
        }
      }
    if (strncasecmp(line, "LBL ",4) == 0) {
      ClearFlag(22);
      ProgramByte(0x00);
      ProgramByte(0xf1);
      ProgramByte(0x00);
      i = 5;
      while (line[i] != 0 && line[i] != '"') {
        if (line[i] > 'e' && line[i] <= 'z') line[i] -= 32;
        ProgramByte(line[i]);
        ram[start-3]++;
        i++;
        }
      Link(start-1);
      }
    if (strncasecmp(line, "GTO ",4) == 0) {
      ClearFlag(22);
      ProgramByte(0xf0);
      i = 5;
      while (line[i] != 0 && line[i] != '"') {
        if (line[i] > 'e' && line[i] <= 'z') line[i] -= 32;
        ProgramByte(line[i]);
        ram[start-2]++;
        i++;
        }
      }
    if (strcasecmp(line, "END") == 0) {
      ClearFlag(22);
      ProgramByte(0x00);
      ProgramByte(0x0d);
      Link(start-1);
      }
    }
  else if (isize(REG_R+1) > 1) {
    ProgramByte(ram[REG_R+0]);
    }
  if (ram[REG_R+1] == 0xd0 || ram[REG_R+1] == 0xe0) {
    ProgramByte(((ram[REG_E+2] & 0x0f) << 4) | 
                ((ram[REG_E+1] & 0xf0) >> 4));
    }
  reg = start / 7;
  byt = start % 7;
  addr = (byt << 12) | reg;
  ram[REG_B+1] = (addr >> 8) & 0xff;
  ram[REG_B+0] = addr & 0xff;
  if (!FlagSet(22)) lineNumber++;
  ram[REG_E+0] = lineNumber & 0xff;
  ram[REG_E+1] &= 0xf0;
  ram[REG_E+1] |= ((lineNumber >> 8) & 0x0f);
  if (byteCount != 0) {
    gaddr = FindNextGlobal(start-2);
    l = ((ram[gaddr] & 0x0f) << 8) | ram[gaddr-1];
    if (l != 0) {
      greg = l & 0x1ff;
      gbyt = (l >> 9) & 0x7;
      d = (greg * 7) + gbyt;
      d += byteCount;
      greg = d / 7;
      gbyt = d % 7;
      ram[gaddr] &= 0xf0;
      ram[gaddr] |= (gbyt << 1) | (greg >> 8);
      ram[gaddr-1] = greg & 0xff;
      }
    }


  }

