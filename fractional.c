#include "header.h"

NUMBER Fractional(NUMBER a) {
  int i;
  int e;
  if (a.esign != 0) return a;
  e = (a.exponent[0] * 10) + a.exponent[1];
  while (e >= 0) {
    for (i=0; i<9; i++) a.mantissa[i] = a.mantissa[i+1];
    e--;
    }
  while (a.mantissa[0] == 0 && IsZero(a) == 0) {
    for (i=0; i<9; i++) a.mantissa[i] = a.mantissa[i+1];
    e--;
    }
  if (IsZero(a)) return ZERO;
  a.esign = 9;
  e = -e;
  a.exponent[0] = e / 100;
  a.exponent[1] = e % 100;
  return a;
  }

