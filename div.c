#include "header.h"

NUMBER Div(NUMBER a, NUMBER b) {
  DNUMBER da;
  DNUMBER db;
  DNUMBER dc;
  if (IsZero(b)) {
    Message("DATA ERROR");
    Error();
    return b;
    }
  da = NumberToDNumber(a);
  db = NumberToDNumber(b);
  dc = D_Div(da, db);
  return DNumberToNumber(dc);
  }

