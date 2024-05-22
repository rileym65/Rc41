#include "header.h"

int FromPtr(int ptr) {
  return ((ptr & 0xfff) * 7) + ((ptr >> 12) & 0xf);
  }

