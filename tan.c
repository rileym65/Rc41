#include "header.h"

NUMBER Tan(NUMBER a) {
  int i;
  NUMBER x;
  NUMBER s;
  NUMBER c;
  s = Sin(a);
  c = Cos(a);
  x = Div(s, c);
  return x;
  }

