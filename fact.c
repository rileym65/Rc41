#include "header.h"

NUMBER Fact(NUMBER a) {
  int i;
  int n;
  double r;
  char tmp[24];
  if (a.esign != 0) {
    Message("DATA ERROR");
    Error();
    return a;
    }
  if (a.exponent[0] != 0) {
    Message("DATA ERROR");
    Error();
    return a;
    }
  for (i=a.exponent[1]+1; i<10; i++)
    if (a.mantissa[i] != 0) {
      Message("NONEXISTENT");
      Error();
      return a;
      }
  n = a.mantissa[0];
  for (i=1; i<=a.exponent[1]; i++) {
    n *= 10;
    n += a.mantissa[i];
    }
  if (n > 69) {
    Message("OUT OF RANGE");
    Error();
    }
  r = 1;
  for (i=1; i<= n; i++) {
    r *= i;
    }
  sprintf(tmp,"%.10e",r);
  a = AtoN(tmp);
  return a;

  }

