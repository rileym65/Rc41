#include "header.h"

NUMBER Mul(NUMBER a, NUMBER b) {
  int i;
  int j;
  int c;
  int ea,eb;
  byte temp[21];
  int p;
  p=9;
  ea = (a.exponent[0] * 10) + a.exponent[1];
  eb = (b.exponent[0] * 10) + b.exponent[1];
  if (a.esign != 0) ea = -ea;
  if (b.esign != 0) eb = -eb;
  a.sign = (a.sign == b.sign) ? 0 : 9;
  ea += eb;
  for (i=0; i<21; i++) temp[i] = 0;
  for (p=9; p>=0; p--) {
    for (i = 0; i<b.mantissa[p]; i++) {
      c = 0;
      for (j=9; j>=0; j--) {
        temp[p+j+2] += (a.mantissa[j] + c);
        if (temp[p+j+2] >= 10) {
          temp[p+j+2] -= 10;
          c = 1;
          }
        else c=0;
        }
      if (c) {
        temp[p+1]++;
        }
      }
    }
  p = 1;
  ea++;
  while (temp[p] == 0) {
    p++;
    ea--;
    }
  for (i=0; i<9; i++)
    a.mantissa[i] = temp[p+i];
  a.esign = (ea < 0) ? 9 : 0;
  if (ea < 0) ea = -ea;
  a.exponent[0] = ea / 10;
  a.exponent[1] = ea % 10;
  return a;
  }

