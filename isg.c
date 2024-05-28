#include "header.h"

int Isg(byte post) {
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
ShowNumber(x);
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
    if (e >= -1) {
      final = (final * 10);
      if (p < 10) final += x.mantissa[p++];
      }
    e++;
    }
  for (i=0; i<2; i++) {
    inc = (inc * 10);
    if (p < 10) inc += x.mantissa[p++];
    }
  if (inc == 0) inc = 1;
  if (x.sign) count = -count;
printf("Count = %d\n",count);
printf("Final = %d\n",final);
printf("Inc   = %d\n",inc);
  count += inc;
  sprintf(tmp,"%d.%03d%02d",count,final,inc);
printf("-->%s\n",tmp);
  y = AtoN(tmp);
  if (count < 0) y.sign = 9;
  Sto(y, post);
if (count > final) printf("Skip\n");
  if (count > final) return -1;
  return 0;
  }

