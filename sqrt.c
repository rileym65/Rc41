#include "header.h"

NUMBER Sqrt(NUMBER a) {
  int i;
  int flag;
  DNUMBER x;
  DNUMBER e;
  DNUMBER last;
  DNUMBER t;
  if (a.sign) {
    Message("DATA ERROR");
    Error();
    return a;
    }
  x = NumberToDNumber(a);
  e = D_Div(x, D_TWO);

  flag = -1;
  while (flag) {
    last = e;
    t = D_Div(x, e);
    t = D_Add(t, e);
    e = D_Mul(t, D_HALF);

    flag = 0;
    for (i=0; i<15; i++)
      if (last.mantissa[i] != e.mantissa[i]) flag = -1;
    }
  return DNumberToNumber(e);
  }

