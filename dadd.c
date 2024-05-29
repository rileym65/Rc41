#include "header.h"

void d_tens(int *n) {
  int i;
  int c;
  for (i=0; i<20; i++) n[i] = 9 - n[i];
  c = 1;
  for (i=19; i>=0; i--) {
    n[i] += c;
    if (n[i] > 9) {
      n[i] -= 10;
      c = 1;
      }
    else c = 0;
    }
  }

DNUMBER D_Add(DNUMBER a, DNUMBER b) {
  int     i;
  int     ea;
  int     eb;
  int     c;
  int     addsub;
  int     temp1[20];
  int     temp2[20];
  DNUMBER result;
  addsub = (a.sign == b.sign) ? 0 : 1;
  ea = (a.exponent[0] * 100) + (a.exponent[1] * 10) + a.exponent[2];
  eb = (b.exponent[0] * 100) + (b.exponent[1] * 10) + b.exponent[2];
  if (a.esign) ea = -ea;
  if (b.esign) eb = -eb;
  for (i=0; i<20; i++) {
    temp1[i] = a.mantissa[i];
    temp2[i] = b.mantissa[i];
    }
  while (ea > eb) {
    for (i=19; i>= 0; i--) temp2[i] = temp2[i-1];
    temp2[0] = 0;
    eb++;
    }
  while (eb > ea) {
    for (i=19; i>= 0; i--) temp1[i] = temp1[i-1];
    temp1[0] = 0;
    ea++;
    }
  c = 0;
  for (i=0; i<20; i++) c+= temp1[i]; 
  if (c == 0) return b;
  c = 0;
  for (i=0; i<20; i++) c+= temp2[i]; 
  if (c == 0) return a;
  if (addsub != 0) {
    if (a.sign != 0) d_tens(temp1);
    if (b.sign != 0) d_tens(temp2);
    }
  c = 0;
  for (i=19; i>=0; i--) {
      temp1[i] += (temp2[i] + c);
      if (temp1[i] >= 10) {
        temp1[i] -= 10;
        c = 1;
        }
      else c = 0;
    }
  result.sign = a.sign;
  if (addsub) {
    if (c == 0) {
      d_tens(temp1);
 if (result.sign == 0) result.sign = 9;
      }
    if (c == 1 && result.sign != 0) result.sign = 0;
    }
  if (addsub == 0 && c) {
    for (i=19; i>0; i--) temp1[i] = temp1[i-1];
    temp1[0] = 1;
    ea++;
    }
  while (temp1[0] == 0 &&
         (temp1[1] != 0 || temp1[2] != 0 ||
          temp1[3] != 0 || temp1[4] != 0 ||
          temp1[5] != 0 || temp1[6] != 0 ||
          temp1[7] != 0 || temp1[8] != 0 ||
          temp1[9] != 0 || temp1[10] != 0 ||
          temp1[11] != 0 || temp1[12] != 0 ||
          temp1[13] != 0 || temp1[14] != 0 ||
          temp1[15] != 0 || temp1[16] != 0 ||
          temp1[17] != 0 || temp1[18] != 0 ||
          temp1[19])) {
    for (i=0; i<19; i++) temp1[i] = temp1[i+1];
    temp1[19] = 0;
    ea--;
    }
  if (ea >= 0) result.esign = 0; else result.esign = 9;
  if (ea < 0) ea = -ea;
  result.exponent[0] = (ea / 100);
  ea = ea % 100;
  result.exponent[1] = (ea / 10);
  result.exponent[2] = (ea % 10);
  for (i=0; i<20; i++) result.mantissa[i] = temp1[i];
  return result;
  }


