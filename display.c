#include "header.h"

char* Display(char* buffer) {
  NUMBER a;
  if (FlagSet(52)) {
    ProgramLine(buffer);
    }
  else if (FlagSet(50)) {
    strcpy(buffer, display);
    }
  else if (FlagSet(48)) {
   
    }
  else {
    a = RecallNumber(R_X);
    Format(a,buffer);
    }
  while (strlen(buffer) < 12) strcat(buffer," ");
  return buffer;
  }
