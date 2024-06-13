#include "header.h"

/* ************************************************* */
/* ***** Returns ram address from NABC address ***** */
/* ************************************************* */
int FromPtr(int ptr) {
  return ((ptr & 0xfff) * 7) + ((ptr >> 12) & 0xf);
  }

