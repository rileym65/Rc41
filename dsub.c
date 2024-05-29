#include "header.h"

DNUMBER D_Sub(DNUMBER a, DNUMBER b) {
  b.sign = (b.sign == 0) ? 9 : 0;
  return D_Add(a,b);
  }

