#include "header.h"

NUMBER Sin(NUMBER a) {
  int i;
  DNUMBER x;
  DNUMBER fact;
  DNUMBER one;
  DNUMBER sum;
  DNUMBER sqr;
  DNUMBER num;
  DNUMBER den;
  DNUMBER term;
  int     addsub;
  x = NumberToDNumber(a);
  one.sign = 0;
  one.esign = 0;
  one.mantissa[0] = 1;
  for (i=1; i<20; i++) one.mantissa[i] = 0;
  for (i=0; i<3; i++) one.exponent[i] = 0;
  sum = x;
  den = one;
  fact = one;
  fact.mantissa[0] = 2;
  num = x;
  sqr = D_Mul(x, x);
  addsub = -1;
  while (den.exponent[1] <= 2) {
    num = D_Mul(num, sqr);
    den = D_Mul(den,fact);
    fact = D_Add(fact, one);
    den = D_Mul(den,fact);
    fact = D_Add(fact, one);
    term = D_Div(num, den);
    term.sign = (addsub) ? 9 : 0;
    addsub = (addsub) ? 0 : -1;
    sum = D_Add(sum, term);
    }
  return DNumberToNumber(sum);
  }

