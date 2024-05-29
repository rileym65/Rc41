#include "header.h"

NUMBER Atan(NUMBER a) {
  int     i;
  int     flag;
  int     addsub;
  DNUMBER x;
  DNUMBER xsqr;
  DNUMBER one = { 0, { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
  DNUMBER two = { 0, { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
  DNUMBER pi2 = { 0, { 1,5,7,0,7,9,6,3,2,6,7,9,4,8,9,6,6,1,9,2 }, 0, { 0,0,0 } };
  DNUMBER sum;
  DNUMBER den;
  DNUMBER last;
  DNUMBER term;
  x = NumberToDNumber(a);
  xsqr = D_Mul(x, x);
  addsub = -1;
  if (x.esign != 0) {
    den = two;
    den.mantissa[0] = 3;
    sum = x;
    flag = -1;
    while (flag) {
      last = sum;
      x = D_Mul(x, xsqr);
      term = D_Div(x, den);
      if (addsub) sum = D_Sub(sum, term);
        else sum = D_Add(sum, term);
      addsub = (addsub) ? 0 : -1;
      den = D_Mul(den, two);
      flag = 0;
      for (i=0; i<15; i++)
        if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
      }
    }
  else {
    sum = pi2;
    den = one;
    while (flag) {
      last = sum;
      den = D_Mul(den, x);
      term = D_Div(one, den);
      if (addsub) sum = D_Sub(sum, term);
        else sum = D_Add(sum, term);
      addsub = (addsub) ? 0 : -1;
      den = D_Add(den, two);
      x = D_Mul(x, xsqr);
      flag = 0;
      for (i=0; i<15; i++)
        if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
      }
    sum.sign = a.sign;
    }

  return DNumberToNumber(x);
  }

