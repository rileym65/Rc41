#include "header.h"

void Push(int address) {
  int i;
printf("push: [%04x] %02x %02x %02x\n",ToPtr(address),ram[address],ram[address-1],ram[address-2]);
  address = ToPtr(address);
  for (i=6; i>1; i--) ram[REG_A+i] = ram[REG_A+i-2];
  ram[REG_A+1] = ram[REG_B+6];
  ram[REG_A+0] = ram[REG_B+5];
  for (i=6; i>1; i--) ram[REG_B+i] = ram[REG_B+i-2];
  ram[REG_B+3] = (address >> 8) & 0xff;
  ram[REG_B+2] = address & 0xff;
  }

