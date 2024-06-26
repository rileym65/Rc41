#include "header.h"

void EndNumber() {
  int i;
  NUMBER nm;
  if (!FlagSet(22)) return;
  ClearFlag(22);
  nm = RecallNumber(R_X);
  i = (nm.exponent[0] * 10) + nm.exponent[1];
  if (nm.esign) i = -i;
  ex += i;
  nm.esign = (ex < 0) ? 9 : 0;
  if (ex < 0) ex = -ex;
  nm.exponent[0] = ex / 10;
  nm.exponent[1] = ex % 10;
  StoreNumber(nm, R_X);
  ram[LIFT] = 'E';
  }

