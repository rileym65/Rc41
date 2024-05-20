#include "header.h"

void ShowStatRegs(int stackOnly) {
  int i;

  if (stackOnly == 0) {
    printf(" e: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_E*7+i]);
    printf("\n");
  
    printf(" d: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_D*7+i]);
    printf("\n");
  
    printf(" c: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_C*7+i]);
    printf("\n");
  
    printf(" b: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_B*7+i]);
    printf("\n");
  
    printf(" a: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_A*7+i]);
    printf("\n");
  
    printf("|-: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_R*7+i]);
    printf("\n");
  
    printf(" Q: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_Q*7+i]);
    printf("\n");
  
    printf(" P: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_P*7+i]);
    printf("\n");
  
    printf(" O: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_O*7+i]);
    printf("\n");
  
    printf(" N: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_N*7+i]);
    printf("\n");
  
    printf(" M: ");
    for (i=6; i>=0; i--)
    printf("%02x ",ram[REG_M*7+i]);
    printf("\n");
    }

  printf(" L: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_L*7+i]);
  printf("\n");

  printf(" X: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_X*7+i]);
  printf("\n");

  printf(" Y: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_Y*7+i]);
  printf("\n");

  printf(" Z: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_Z*7+i]);
  printf("\n");

  printf(" T: ");
  for (i=6; i>=0; i--)
  printf("%02x ",ram[REG_T*7+i]);
  printf("\n");

  }

