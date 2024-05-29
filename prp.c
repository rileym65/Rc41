#include "header.h"

void Prp(char* name) {
  int lineNumber;
  int address;
  int end;
  char line[256];
  address = FindGlobal(name);
  if (address == 0) return;
  address = FindStart(address);
  end = FindEnd(address);
  lineNumber = 1;
  printf("\n");
  while (ram[address] == 0x00) address--;
  while (address >= end) {
    ProgramList(lineNumber, address, line);
    printf("%s\n",line);
    lineNumber++;
    address -= isize(address);
    while (ram[address] == 0x00) address--;
    }
  }

