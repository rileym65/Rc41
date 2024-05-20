#include "header.h"

NUMBER Integer(NUMBER a) {
  int i;
  int e;
  if (a.esign != 0) return ZERO;
  e = (a.exponent[0] * 10) + a.exponent[1];
  if (e < 10) {
    for (i=1+e; i<10; i++) a.mantissa[i] = 0;
    }
  return a;
  }

