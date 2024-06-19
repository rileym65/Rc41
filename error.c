#include "header.h"

void Error() {
  if (FlagSet(25)) {
    ClearFlag(25);
    return;
    }
  errFlag = -1;
  running = 0;
  }

