#include "header.h"

NUMBER Ex(NUMBER a) {
  int i;
  int flag;
  DNUMBER one;
  DNUMBER n;
  DNUMBER x;
  DNUMBER sum;
  DNUMBER num;
  DNUMBER den;
  DNUMBER term;
  DNUMBER base;
  DNUMBER last;
  DNUMBER fact;
  int     addsub;
  x = NumberToDNumber(a);
  one.sign = 0;
  one.esign = 0;
  one.mantissa[0] = 1;
  for (i=1; i<20; i++) one.mantissa[i] = 0;
  for (i=0; i<3; i++) one.exponent[i] = 0;
  sum = D_Add(x, one);
  num = x;
  den = one;
  fact = one;
  flag = -1;
  while (flag) {
    last = sum;
    num = D_Mul(num, x);
    fact = D_Add(fact, one);
    den = D_Mul(den, fact);
    term = D_Div(num, den);
    sum = D_Add(sum, term);
    flag = 0;
    for (i=0; i<15; i++)
      if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
    }
  return DNumberToNumber(sum);
  }

