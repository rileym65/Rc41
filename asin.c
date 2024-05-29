#include "header.h"

NUMBER Asin(NUMBER a) {
  int i;
  int flag;
  DNUMBER one = { 0, { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
  DNUMBER two = { 0, { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
  DNUMBER x;
  DNUMBER xsqr;
  DNUMBER sum;
  DNUMBER num;
  DNUMBER den;
  DNUMBER term1;
  DNUMBER term2;
  DNUMBER fact = { 0, { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
  DNUMBER last;
  x = NumberToDNumber(a);
  xsqr = D_Mul(x, x);
  sum = x;
  num = one;
  den = two;

  flag = -1;
  while (flag) {
    last = sum;
    x = D_Mul(x, xsqr);
    term1 = D_Mul(num, x);
    term2 = D_Mul(den, fact);
    term1 = D_Div(term1, term2);
    sum = D_Add(sum, term1);
    
    num = D_Mul(num, fact);
    fact = D_Add(fact, one);
    den = D_Mul(den, fact);
    fact = D_Add(fact, one);

    flag = 0;
    for (i=0; i<15; i++)
      if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
    }
  return DNumberToNumber(sum);
  }

