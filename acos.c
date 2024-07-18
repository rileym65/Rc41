#include "header.h"

NUMBER Acos(NUMBER a) {
  a = Asin(a);
  return Sub(S_PI2, a);
  }

