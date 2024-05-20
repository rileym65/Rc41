#include "header.h"

void ShowNumber(NUMBER n) {
  int i;
  if (n.sign == 0) printf("+"); else printf("-");
  printf("%c.",n.mantissa[0]+'0');
  for (i=1; i<10; i++)
    printf("%c",n.mantissa[i]+'0');
  printf(" E");
  if (n.esign == 0) printf("+"); else printf("-");
  printf("%c%c\n",n.exponent[0]+'0', n.exponent[1]+'0');
  }

