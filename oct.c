#include "header.h"

NUMBER Oct(NUMBER a) {
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
  n = a.mantissa[0];
  for (i=1; i<=a.exponent[1]; i++) {
    n *= 10;
    n += a.mantissa[i];
    }
  if (n > 1073741823) {
    Message("DATA ERROR");
    Error();
    return a;
    }
  tmp[10] = 0;
  i = 9;
  while (i>=0 ) {
    tmp[i] = (n & 0x7) + '0';
    n >>= 3;
    i--;
    }
  printf("-->%s\n",tmp);
  a = AtoN(tmp);
  return a;
  }

