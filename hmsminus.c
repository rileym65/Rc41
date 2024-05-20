#include "header.h"

NUMBER HmsMinus(NUMBER a, NUMBER b) {
  a.sign = (a.sign) ? 0 : 9;
  return HmsPlus(a, b);
  }

