#include <iostream>
#include "blue.h"
#include "red.h"

// In order to link dynamic library, please set path to it
// export LD_LIBRARY_PATH=<path to dynamic library>:$LD_LIBRARY_PATH

int main()
{

  blue(123);
  red(43534);

  return 0;
}
