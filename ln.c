#include "header.h"

NUMBER Ln(NUMBER a) {
  int i;
  int flag;
  DNUMBER one;
  DNUMBER two;
  DNUMBER n;
  DNUMBER x;
  DNUMBER sum;
  DNUMBER num;
  DNUMBER term;
  DNUMBER base;
  DNUMBER last;
  x = NumberToDNumber(a);
  one.sign = 0;
  one.esign = 0;
  one.mantissa[0] = 1;
  for (i=1; i<20; i++) one.mantissa[i] = 0;
  for (i=0; i<3; i++) one.exponent[i] = 0;
  two = one;
  two.mantissa[0] = 2;
  sum = D_Div(D_Sub(x, one), D_Add(x, one));
  n = D_Mul(sum, sum);
  base = sum;
  num = one;
  flag = -1;
  while (flag) {
    last = sum;
    base = D_Mul(base, n);
    num = D_Add(num, two);
    term = D_Div(one, num);
    term = D_Mul(term, base);
    sum = D_Add(sum, term);
    flag = 0;
    for (i=0; i<15; i++)
      if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
    }
  sum = D_Add(sum, sum);
  return DNumberToNumber(sum);
  }

