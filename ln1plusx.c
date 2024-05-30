#include "header.h"

NUMBER Ln1PlusX(NUMBER a) {
  int i;
  int flag;
  int cnt;
  DNUMBER one;
  DNUMBER x;
  DNUMBER sum;
  DNUMBER num;
  DNUMBER den;
  DNUMBER term;
  DNUMBER last;
  int     addsub;
  x = NumberToDNumber(a);
  one.sign = 0;
  one.esign = 0;
  one.mantissa[0] = 1;
  for (i=1; i<20; i++) one.mantissa[i] = 0;
  for (i=0; i<3; i++) one.exponent[i] = 0;
  sum = x;
  num = x;
  den = one;
  addsub = -1;
  flag = -1;
cnt = 0;
  while (flag) {
cnt++;
    last = sum;
    num = D_Mul(num, x);
    den = D_Add(den, one);
    term = D_Div(num, den);
    if (addsub) {
      sum = D_Sub(sum, term);
      addsub = 0;
      }
    else {
      sum = D_Add(sum, term);
      addsub = -1;
      }
    flag = 0;
    for (i=0; i<15; i++)
      if (last.mantissa[i] != sum.mantissa[i]) flag = -1;
    }
printf("Count = %d\n",cnt);
  return DNumberToNumber(sum);
  }

