#include "header.h"

NUMBER RecallNumber(int reg) {
  NUMBER a;
  reg *= 7;
  a.sign = (ram[reg+6] >> 4) & 0xf;
  a.mantissa[0] = ram[reg+6] & 0xf;
  a.mantissa[1] = (ram[reg+5] >> 4) & 0xf;
  a.mantissa[2] = ram[reg+5] & 0xf;
  a.mantissa[3] = (ram[reg+4] >> 4) & 0xf;
  a.mantissa[4] = ram[reg+4] & 0xf;
  a.mantissa[5] = (ram[reg+3] >> 4) & 0xf;
  a.mantissa[6] = ram[reg+3] & 0xf;
  a.mantissa[7] = (ram[reg+2] >> 4) & 0xf;
  a.mantissa[8] = ram[reg+2] & 0xf;
  a.mantissa[9] = (ram[reg+1] >> 4) & 0xf;
  a.esign = ram[reg+1] & 0xf;
  a.exponent[0] = (ram[reg+0] >> 4) & 0xf;
  a.exponent[1] = ram[reg+0] & 0xf;
  return a;
  }

