#include "header.h"

int Dse(byte post) {
  int i;
  int p;
  int e;
  int count;
  int final;
  int inc;
  NUMBER x;
  NUMBER y;
  char   tmp[16];
  x = Rcl(post);
  e = x.exponent[0] * 10 + x.exponent[1];
  if (x.esign) e = -e;
  count = 0;
  final = 0;
  inc = 0;
  p = 0;
  while (e >= 0) {
    count *= 10;
    if (p < 10) count += x.mantissa[p++];
    e--;
    }
  for (i=0; i<3; i++) {
    final = (final * 10);
    if (p < 10) final += x.mantissa[p++];
    }
  for (i=0; i<2; i++) {
    inc = (inc * 10);
    if (p < 10) inc += x.mantissa[p++];
    }
  if (inc == 0) inc = 1;
  if (x.sign) count = -count;
  count -= inc;
  sprintf(tmp,"%d.%03d%02d",count,final,inc);
  y = AtoN(tmp);
  if (count < 0) y.sign = 9;
  Sto(y, post);
  if (count <= final) return -1;
  return 0;
  }

