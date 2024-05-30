#include "header.h"

void tens(int *n) {
  int i;
  int c;
  for (i=0; i<21; i++) n[i] = 9 - n[i];
  c = 1;
  for (i=20; i>=0; i--) {
    n[i] += c;
    if (n[i] > 9) {
      n[i] -= 10;
      c = 1;
      }
    else c = 0;
    }
  }

DNUMBER NumberToDNumber(NUMBER a) {
  int i;
  DNUMBER r;
  r.sign = a.sign;
  r.esign = a.esign;
  for (i=0; i<10; i++) r.mantissa[i] = a.mantissa[i];
  for (i=10; i<20; i++) r.mantissa[i] = 0;
  r.exponent[0] = 0;
  r.exponent[1] = a.exponent[0];
  r.exponent[2] = a.exponent[1];
  return r;
  }

NUMBER DNumberToNumber(DNUMBER a) {
  int i;
  NUMBER r;
  r.sign = a.sign;
  r.esign = a.esign;
  for (i=0; i<10; i++) r.mantissa[i] = a.mantissa[i];
  r.exponent[0] = a.exponent[1];
  r.exponent[1] = a.exponent[2];
  return r;
  }

NUMBER Add(NUMBER a, NUMBER b) {
  DNUMBER da;
  DNUMBER db;
  DNUMBER dc;
  da = NumberToDNumber(a);
  db = NumberToDNumber(b);
  dc = D_Add(da, db);
  return DNumberToNumber(dc);
  }


