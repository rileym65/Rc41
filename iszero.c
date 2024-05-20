#include "header.h"

int IsZero(NUMBER a) {
  int i;
  for (i=0; i<10; i++)
    if (a.mantissa[i] != 0) return 0;
  return -1;
  }

