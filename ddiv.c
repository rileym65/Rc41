#include "header.h"

DNUMBER D_Div(DNUMBER a, DNUMBER b) {
  int i;
  int c;
  int ea,eb;
  int f;
  int temp1[21];
  int temp2[21];
  int p;
  int flag;
  DNUMBER result;
  p=9;
  ea = (a.exponent[0] * 100) + (a.exponent[1] * 10) + a.exponent[2];
  eb = (b.exponent[0] * 100) + (b.exponent[1] * 10) + b.exponent[2];
  if (a.esign != 0) ea = -ea;
  if (b.esign != 0) eb = -eb;
  result.sign = (a.sign == b.sign) ? 0 : 9;

  for (i=0; i<20; i++) {
    temp1[i] = a.mantissa[i];
    temp2[i] = b.mantissa[i];
    result.mantissa[i] = 0;
    }

  p = 0;
  while (p < 20) {
    c = 0;
    for (i=0; i<20; i++) c += temp1[i];
    if (c != 0) {
      f = 0;
      for (i=0; i<20; i++) {
        if (temp1[i] > temp2[i]) { f=1; i = 22; }
        else if (temp1[i] < temp2[i]) { f=-1; i=22; }
        }
      if (f >= 0) {
        result.mantissa[p]++;
        c = 0;
        for (i=19; i>=0; i--) {
          temp1[i] -= (temp2[i]+c);
          if (temp1[i] < 0) {
            temp1[i] += 10;
            c = 1;
            } else c = 0;
          }
        }
      else {
        for (i=19; i>0; i--) temp2[i] = temp2[i-1];
        temp2[0] = 0;
        p++;
        }
      } else p = 20;
    }
  flag = -1;
  while (result.mantissa[0] == 0 && flag) {
    flag = 0;
    for (i=0; i<18; i++) {
      result.mantissa[i] = result.mantissa[i+1];
      if (result.mantissa[i] != 0) flag = -1;
      }
    result.mantissa[19] = 0;
    ea--;
    }
  ea -= eb;
  result.esign = (ea < 0) ? 9 : 0;
  if (ea < 0) ea = -ea;
  result.exponent[0] = (ea / 100);
  ea = ea % 100;
  result.exponent[1] = (ea / 10);
  result.exponent[2] = (ea % 10);
  return result;
  }

