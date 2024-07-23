#include "header.h"

void Sf(byte n) {
  n = GetPost(n);
  if (errFlag) return;
  if (n >= 30) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  SetFlag(n);
  }

