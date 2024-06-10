#include "header.h"

void Error() {
  if (FlagSet(25)) {
    ClearFlag(25);
    return;
    }
  running = 0;
  }

