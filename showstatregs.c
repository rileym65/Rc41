#include "header.h"

void ShowStatRegs(int stackOnly) {
  int i;

  if (stackOnly == 0) {
    printf(" e: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_E+i]);
    printf("\n");
  
    printf(" d: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_D+i]);
    printf("\n");
  
    printf(" c: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_C+i]);
    printf("\n");
  
    printf(" b: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_B+i]);
    printf("\n");
  
    printf(" a: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_A+i]);
    printf("\n");
  
    printf("|-: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_R+i]);
    printf("\n");
  
    printf(" Q: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_Q+i]);
    printf("\n");
  
    printf(" P: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_P+i]);
    printf("\n");
  
    printf(" O: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_O+i]);
    printf("\n");
  
    printf(" N: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_N+i]);
    printf("\n");
  
    printf(" M: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_M+i]);
    printf("\n");
    }

  printf(" L: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_L+i]);
  printf("\n");

  printf(" X: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_X+i]);
  printf("\n");

  printf(" Y: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_Y+i]);
  printf("\n");

  printf(" Z: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_Z+i]);
  printf("\n");

  printf(" T: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_T+i]);
  printf("\n");

  }

