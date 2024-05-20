#include "header.h"

NUMBER Div(NUMBER a, NUMBER b) {
  int i;
  int c;
  int ea,eb;
  int f;
  int temp1[21];
  int temp2[21];
  int p;
  p=9;
  ea = (a.exponent[0] * 10) + a.exponent[1];
  eb = (b.exponent[0] * 10) + b.exponent[1];
  if (a.esign != 0) ea = -ea;
  if (b.esign != 0) eb = -eb;
  a.sign = (a.sign == b.sign) ? 0 : 9;

  for (i=0; i<21; i++) {
    temp1[i] = (i <10) ? a.mantissa[i] : 0;
    temp2[i] = (i <10) ? b.mantissa[i] : 0;
    if (i < 10) a.mantissa[i] = 0;
    }

// printf("A:"); for (i=0; i<21; i++) printf(" %d",temp1[i]); printf(" E %d\n",ea);
// printf("B:"); for (i=0; i<21; i++) printf(" %d",temp2[i]); printf(" E %d\n",eb);

  p = 0;
  while (p < 10) {
// printf("p=%d\n",p);
// printf("A:"); for (i=0; i<21; i++) printf(" %d",temp1[i]); printf("\n");
// printf("B:"); for (i=0; i<21; i++) printf(" %d",temp2[i]); printf("\n");
    c = 0;
    for (i=0; i<21; i++) c += temp1[i];
    if (c != 0) {
      f = 0;
      for (i=0; i<21; i++) {
        if (temp1[i] > temp2[i]) { f=1; i = 22; }
        else if (temp1[i] < temp2[i]) { f=-1; i=22; }
        }
      if (f >= 0) {
        a.mantissa[p]++;
        c = 0;
        for (i=20; i>=0; i--) {
          temp1[i] -= (temp2[i]+c);
          if (temp1[i] < 0) {
            temp1[i] += 10;
            c = 1;
            } else c = 0;
          }
        }
      else {
        for (i=20; i>0; i--) temp2[i] = temp2[i-1];
        temp2[0] = 0;
        p++;
        }
      } else p = 10;
    }
  while (a.mantissa[0] == 0) {
    for (i=0; i<9; i++) a.mantissa[i] = a.mantissa[i+1];
    a.mantissa[9] = 0;
    ea--;
    }
  ea -= eb;
  a.esign = (ea < 0) ? 9 : 0;
  if (ea < 0) ea = -ea;
  a.exponent[0] = ea / 10;
  a.exponent[1] = ea % 10;
  return a;
  }

