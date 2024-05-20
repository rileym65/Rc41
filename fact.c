#include "header.h"

NUMBER Fact(NUMBER a) {
  int i;
  int n;
  double r;
  char tmp[16];
  if (a.esign != 0) {
    Message("DATA ERROR");
    return a;
    }
  if (a.exponent[0] != 0) {
    Message("DATA ERROR");
    return a;
    }
  for (i=a.exponent[1]+1; i<10; i++)
    if (a.mantissa[i] != 0) {
      Message("NONEXISTENT");
      return a;
      }
  n = a.mantissa[0];
  for (i=1; i<=a.exponent[1]; i++) {
    n *= 10;
    n += a.mantissa[i];
    }
  if (n > 69) {
    Message("OUT OF RANGE");
    }
  r = 1;
  for (i=1; i<= n; i++) {
    r *= i;
    }
  sprintf(tmp,"%.10e",r);
  a = AtoN(tmp);
  return a;

  }

