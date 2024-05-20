#include "header.h"

void Sf(byte n) {
  NUMBER a;
  if (n >= 0x80 && n <= 0xef) {
    a = Rcl(n & 0x7f);
    n = ToInteger(a);
    }
  else if (n >= 0xf0) {
    a = RecallNumber(n & 0x0f);
    n = ToInteger(a);
    }
  if (n >= 30) {
    Message("NONEXISTENT");
    return;
    }
  SetFlag(n);
  }

