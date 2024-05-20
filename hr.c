#include "header.h"

NUMBER Hr(NUMBER a) {
  int h,m,s,f;
  char tmp[16];
  double d;
  GetHms(a, &h, &m, &s, &f);
  d = m * 60 + s + ((double)f/100.0);
  d /= 3600.0;
  d += h;
  sprintf(tmp,"%.12e\n",d);
printf("<<%s>>\n",tmp);
  a = AtoN(tmp);
  return a;
  }

