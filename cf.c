#include "header.h"

void Cf(byte n) {
  n = GetPost(n);
  if (errFlag) return;
  if (n >= 30) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  ClearFlag(n);
  }

