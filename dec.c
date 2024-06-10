#include "header.h"

NUMBER Dec(NUMBER a) {
  int i;
  int n;
  char tmp[16];
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
      Message("DATA ERROR");
      Error();
      return a;
      }
  for (i=0; i<10; i++)
    if (a.mantissa[i] > 7) {
      Message("DATA ERROR");
      Error();
      return a;
      }
  n = a.mantissa[0];
  for (i=1; i<=a.exponent[1]; i++) {
    n *= 8;
    n += a.mantissa[i];
    }
  sprintf(tmp,"%d",n);
  a = AtoN(tmp);
  return a;
  }

