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

NUMBER Add(NUMBER a, NUMBER b) {
  int i;
  int ea;
  int eb;
  int c;
  int addsub;
  int temp1[21];
  int temp2[21];
  addsub = (a.sign == b.sign) ? 0 : 1;
  ea = (a.exponent[0] * 10) + a.exponent[1];
  eb = (b.exponent[0] * 10) + b.exponent[1];
  if (a.esign) ea = -ea;
  if (b.esign) eb = -eb;
  for (i=0; i<21; i++) {
    temp1[i] = (i < 10) ? a.mantissa[i] : 0;
    temp2[i] = (i < 10) ? b.mantissa[i] : 0;
    }
  while (ea > eb) {
    for (i=20; i>= 0; i--) temp2[i] = temp2[i-1];
    temp2[0] = 0;
    eb++;
    }
  while (eb > ea) {
    for (i=20; i>= 0; i--) temp1[i] = temp1[i-1];
    temp1[0] = 0;
    ea++;
    }
  if (addsub != 0) {
    if (a.sign != 0) tens(temp1);
    if (b.sign != 0) tens(temp2);
    }
  c = 0;
  for (i=9; i>=0; i--) {
      temp1[i] += (temp2[i] + c);
      if (temp1[i] >= 10) {
        temp1[i] -= 10;
        c = 1;
        }
      else c = 0;
    }
  if (addsub) {
    if (c == 0) {
      tens(temp1);
 if (a.sign == 0) a.sign = 9;
//      a.sign = (a.sign == 0) ? 9 : 0;
      }
    if (c == 1 && a.sign != 0) a.sign = 0;
    }
  if (addsub == 0 && c) {
    for (i=20; i>0; i--) temp1[i] = temp1[i-1];
    temp1[0] = 1;
    ea++;
    }
  while (temp1[0] == 0 &&
         (temp1[1] != 0 || temp1[2] != 0 ||
          temp1[3] != 0 || temp1[4] != 0 ||
          temp1[5] != 0 || temp1[6] != 0 ||
          temp1[7] != 0 || temp1[8] != 0 ||
          temp1[9])) {
    for (i=0; i<21; i++) temp1[i] = temp1[i+1];
    temp1[20] = 0;
    ea--;
    }
  if (ea >= 0) a.esign = 0; else a.esign = 9;
  if (ea < 0) ea = -ea;
  a.exponent[0] = (ea / 10);
  a.exponent[1] = (ea % 10);
  for (i=0; i<10; i++) a.mantissa[i] = temp1[i];
  return a;
  }


