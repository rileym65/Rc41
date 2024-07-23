#include "header.h"

void Sci(byte n) {
  n = GetPost(n);
  if (errFlag) return;
  if (n >= 0x0a) {
    Message("DATA ERRROR");
    Error();
    return;
    }
  ClearFlag(40);
  ClearFlag(41);
  if (n & 8) SetFlag(36); else ClearFlag(36);
  if (n & 4) SetFlag(37); else ClearFlag(37);
  if (n & 2) SetFlag(38); else ClearFlag(38);
  if (n & 1) SetFlag(39); else ClearFlag(39);
  }

