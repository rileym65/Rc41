#include "header.h"

void SetX(NUMBER n, int l, int s) {
  NUMBER a;
  if (lift != 0 && s != 0) {
    a = RecallNumber(REG_Z);
    StoreNumber(a, REG_T);
    a = RecallNumber(REG_Y);
    StoreNumber(a, REG_Z);
    a = RecallNumber(REG_X);
    StoreNumber(a, REG_Y);
    }
  if (l != 0) {
    a = RecallNumber(REG_X);
    StoreNumber(a, REG_L);
    }
  StoreNumber(n,REG_X);
  lift = 0;
  }

