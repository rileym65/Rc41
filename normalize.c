#include "header.h"

NUMBER Normalize(NUMBER n) {
  int i;
  int e;
  if (IsZero(n)) return n;
  e = (n.exponent[0] * 10) + n.exponent[1];
  if (n.esign) e = -e;
  while (n.mantissa[0] == 0) {
    for (i=0; i<9; i++) n.mantissa[i] = n.mantissa[i+1];
    n.mantissa[9] = 0;
    e--;
    }
  if (e < 0) {
    n.esign = 9;
    e = -e;
    }
  else n.esign = 0;
  n.exponent[0] = e / 10;
  n.exponent[1] = e % 10;
  return n;
  }

