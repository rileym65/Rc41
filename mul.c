#include "header.h"

NUMBER Mul(NUMBER a, NUMBER b) {
  DNUMBER da;
  DNUMBER db;
  DNUMBER dc;
  da = NumberToDNumber(a);
  db = NumberToDNumber(b);
  dc = D_Mul(da, db);
  return DNumberToNumber(dc);
  }

