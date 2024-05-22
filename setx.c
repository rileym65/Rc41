#include "header.h"

void SetX(NUMBER n, int l, int s) {
  NUMBER a;
  if (lift != 0 && s != 0) {
    a = RecallNumber(R_Z);
    StoreNumber(a, R_T);
    a = RecallNumber(R_Y);
    StoreNumber(a, R_Z);
    a = RecallNumber(R_X);
    StoreNumber(a, R_Y);
    }
  if (l != 0) {
    a = RecallNumber(R_X);
    StoreNumber(a, R_L);
    }
  StoreNumber(n,R_X);
  lift = 0;
  }

