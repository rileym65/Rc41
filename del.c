#include "header.h"

void Del(char* token) {
  int addr;
  int n;
  int s;
  int lineNumber;
  if (FlagSet(52) == 0) return;
  n = atoi(token);
  lineNumber = ((ram[REG_E+1] & 0x0f) << 8) | ram[REG_E+0];
  if (lineNumber == 0xfff) {
    FixLineNumber();
    lineNumber = ((ram[REG_E+1] & 0x0f) << 8) | ram[REG_E+0];
    }
  if (lineNumber > 0) lineNumber--;
  addr = FromPtr((ram[REG_B+1] << 8) | ram[REG_B+0]);
  addr--;
  while (n > 0) {
    while (ram[addr] == 0x00) addr--;
    if (ram[addr] >= 0xc0 && ram[addr] <= 0xcd && ram[addr-2] < 0xf0) n = 0;
    else {
      s = isize(addr);
      while (s > 0) {
        ram[addr--] = 0;
        s--;
        }
      n--;
      }
    }
  GotoLine(lineNumber);
  }

