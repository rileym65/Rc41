#include "header.h"

NUMBER Sub(NUMBER a, NUMBER b) {
  b.sign = (b.sign == 0) ? 9 : 0;
  return Add(a,b);
  }

