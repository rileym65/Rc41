#include "header.h"

NUMBER YtoX(NUMBER y, NUMBER x) {
  x = Ln(x);
  x = Mul(x, y);
  x = Ex(x);
  return x;
  }

