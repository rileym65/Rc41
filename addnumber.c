#include "header.h"

void AddNumber(char n) {
  int i;
  NUMBER x;
  ram[PENDING] = 'D';
  if (FlagSet(22) == 0) {
    dp = 0;
    ps = 0;
    ex = -1;
    SetFlag(22);
    x.sign = 0;
    x.esign = 0;
    for (i=0; i<10; i++) x.mantissa[i] = 0;
    x.exponent[0] = 0;
    x.exponent[1] = 0;
    }
  else x = RecallNumber(R_X);
  if (n < 10) {
    if (n == 0 && x.mantissa[0] == 0) {
      if (dp != 0) ex--;
      }
    else {
      if (ps >= 0) {
        if (ps < 10) x.mantissa[ps++] = n;
        if (dp == 0) ex++;
        }
      else {
        if (x.exponent[0] != 0) {
          Message("SIZE ERR");
          return;
          }
        x.exponent[0] = x.exponent[1];
        x.exponent[1] = n;
        }
      }
    }
  if (n == 10) {
    dp = -1;
    }
  if (n == 11 && ps >= 0) {
printf("Numeric EEX\n");
    ps = -1;
    if (x.mantissa[0] == 0) {
      x.mantissa[0] = 1;
      ex++;
      }
    }
  if (n == 12) {
printf("Numeric CHS\n");
    if (ps >= 0) x.sign = (x.sign == 0) ? 9 : 0;
      else x.esign = (x.esign == 0) ? 9 : 0;
    }


  StoreNumber(x, R_X);
  }

// 10 = .
// 11 = EEX
// 12 = CHS
// e.1 
//   1x - decimal entered
//   2x - eex entered
