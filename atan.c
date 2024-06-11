#include "header.h"

NUMBER Atan(NUMBER a) {
  int     i;
  int     flag;
  int     addsub;
  DNUMBER x;
  DNUMBER xsqr;
  DNUMBER sum;
  DNUMBER den;
  DNUMBER last;
  DNUMBER term;
  x = NumberToDNumber(a);
  xsqr = D_Mul(x, x);
  addsub = -1;
  if (x.esign != 0) {
    den = D_TWO;
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
      den = D_Add(den, D_TWO);
      flag = 0;
      for (i=0; i<12; i++)
        if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
      }
    }
  else {
    x.sign = 0;
    sum = D_PI2;
    den = D_ONE;
    flag = -1;
    while (flag) {
      last = sum;
      term = D_Mul(den, x);
      term = D_Div(D_ONE, term);
      if (addsub) sum = D_Sub(sum, term);
        else sum = D_Add(sum, term);
      addsub = (addsub) ? 0 : -1;
      den = D_Add(den, D_TWO);
      x = D_Mul(x, xsqr);
      flag = 0;
      for (i=0; i<12; i++)
        if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
      }
    sum.sign = a.sign;
    }
  return DNumberToNumber(sum);
  }

