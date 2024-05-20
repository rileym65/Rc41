#include "header.h"

NUMBER Hms(NUMBER a) {
  NUMBER b;
  char   tmp[16];
  int    m;
  int    s;
  int    h;
  int    f;
  double y;
  char   n[32];
  NtoA(a, n);
  y = atof(n);
  h = y;
  y -= h;
  y *= 3600;
  m = y / 60;
  y -= m * 60;
  s = y;
  y -= (int)y;
  y *= 100;
  f = y;
  sprintf(tmp,"%02d.%02d%02d%02d\n",h,m,s,f);
  b = AtoN(tmp);
  return b;
  }

