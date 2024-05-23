#include "header.h"

void StoreNumber(NUMBER n, int reg) {
  int i;
  if (reg == R_X && ram[LIFT] == 'E') {
    for (i=0; i<21; i++) ram[i] = ram[i+7];
    }
  reg *= 7;
  ram[reg+6] = (n.sign << 4) | (n.mantissa[0] & 0xf);
  ram[reg+5] = (n.mantissa[1] <<4) | (n.mantissa[2] & 0xf);
  ram[reg+4] = (n.mantissa[3] <<4) | (n.mantissa[4] & 0xf);
  ram[reg+3] = (n.mantissa[5] <<4) | (n.mantissa[6] & 0xf);
  ram[reg+2] = (n.mantissa[7] <<4) | (n.mantissa[8] & 0xf);
  ram[reg+1] = (n.mantissa[9] <<4) | (n.esign & 0xf);
  ram[reg+0] = (n.exponent[0] <<4) | (n.exponent[1] & 0xf);
  }

