#include "header.h"

void Eng(byte n) {
  NUMBER a;
  if (n >= 0x80 && n <= 0xef) {
    a = Rcl(n & 0x7f);
    n = ToInteger(a);
    }
  else if (n >= 0xf0) {
    a = RecallNumber(n & 0x0f);
    n = ToInteger(a);
    }
  if (n >= 0x0a) {
    Message("DATA ERRROR");
    Error();
    return;
    }
  ClearFlag(40);
  SetFlag(41);
  if (n & 8) SetFlag(36); else ClearFlag(36);
  if (n & 4) SetFlag(37); else ClearFlag(37);
  if (n & 2) SetFlag(38); else ClearFlag(38);
  if (n & 1) SetFlag(39); else ClearFlag(39);
  }

