#include "header.h"

NUMBER Acos(NUMBER a) {
  int i;
  NUMBER pi2;
  NUMBER two = { 0, { 2,0,0,0,0,0,0,0,0,0 }, 0, { 0, 0 } };
  pi2 = Div(PI, two);
  a = Asin(a);
  return Sub(pi2, a);
  }

