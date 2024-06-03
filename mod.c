#include "header.h"

NUMBER Mod(NUMBER x, NUMBER y) {
  NUMBER a;
  a = Div(x, y);
  a = Integer(a);
  a = Mul(y, a);
  a = Sub(x, a);
  a.sign = (x.sign != y.sign) ? 9 : 0;
  return a;
  }

