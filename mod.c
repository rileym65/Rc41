#include "header.h"

NUMBER Mod(NUMBER x, NUMBER y) {
  NUMBER a;
ShowNumber(x);
ShowNumber(y);
  a = Div(x, y);
printf("x/y="); ShowNumber(a);
  a = Integer(a);
printf("Int="); ShowNumber(a);
  a = Mul(y, a);
printf("*y="); ShowNumber(a);
  a = Sub(x, a);
printf("x-="); ShowNumber(a);
  a.sign = (x.sign != y.sign) ? 9 : 0;
  return a;
  }

