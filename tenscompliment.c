#include "header.h"

NUMBER TensCompliment(NUMBER a) {
  int i;
  int c;
  c = 1;
  for (i=9; i>=0; i--) {
    a.mantissa[i] = (9 - a.mantissa[i]) + c;
    if (a.mantissa[i] > 9) {
      a.mantissa[i] -= 10;
      c = 1;
      } else c = 0;
    }
  return a;
  }

