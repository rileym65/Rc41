#include "header.h"

void GetHms(NUMBER a, int* h, int* m, int *s, int *f) {
  int e;
  int p;
  e = a.exponent[0] * 10 + a.exponent[1];
  if (a.esign) e = -e;
  p = 0;
  *h = 0;
  *m = 0;
  *s = 0;
  *f = 0;
  while (e >= 0) {
    if (p < 10) *h = (*h * 10) + a.mantissa[p++];
      else *h *= 10;
    e--;
    }
  e++;
  while (e < 0) { p++; e++; }
  if (p < 10) *m = a.mantissa[p++] * 10;
  if (p < 10) *m += a.mantissa[p++];
  if (p < 10) *s = a.mantissa[p++] * 10;
  if (p < 10) *s += a.mantissa[p++];
  if (p < 10) *f = a.mantissa[p++] * 10;
  if (p < 10) *f += a.mantissa[p++];
  if (a.sign) {
    *h = -*h;
    *m = -*m;
    *s = -*s;
    *f = -*f;
    }
  }

NUMBER HmsPlus(NUMBER a, NUMBER b) {
  char   buffer[16];
  int p;
  int e;
  int ha,ma,sa,fa;
  int hb,mb,sb,fb;
  GetHms(a, &ha, &ma, &sa, &fa);
  GetHms(b, &hb, &mb, &sb, &fb);
  fa += fb;
  if (fa >= 100) { fa-=100; sa++; }
  if (fa < 0) { fa+=100; sa--; }
  sa += sb;
  if (sa >= 60) { sa -= 60; ma++; }
  if (sa < 0) { sa += 60; ma--; }
  ma += mb;
  if (ma >= 60) { ma -= 60; ha++; }
  if (ma < 0) { ma += 60; ha--; }
  ha += hb;
  sprintf(buffer,"%d.%02d%02d%02d",ha,ma,sa,fa);
  a = AtoN(buffer);
  return a;
  }

