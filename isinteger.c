#include "header.h"

int IsInteger(NUMBER a) {
  int e;
  e = (a.exponent[0] * 10) + a.exponent[1];
  if (a.esign) return 0;
  e++;
  while (e < 10) {
    if (a.mantissa[e] != 0) return 0;
    e++;
    }
  return -1;
  }

