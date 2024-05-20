#include "header.h"

char* NtoA(NUMBER a,char* buffer) {
  int p;
  int i;
  p = 0;
  if (a.sign) buffer[p++] = '-';
  buffer[p++] = a.mantissa[0] + '0';
  buffer[p++] = '.';
  for (i=1; i<10; i++) {
    buffer[p++] = a.mantissa[i]+'0';
    }
  buffer[p++] = 'E';
  buffer[p++] = (a.esign) ? '-' : '+';
  buffer[p++] = a.exponent[0] + '0';
  buffer[p++] = a.exponent[1] + '0';
  buffer[p++] = 0;
  return buffer;
  }

