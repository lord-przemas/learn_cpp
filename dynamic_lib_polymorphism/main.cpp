#include <iostream>
#include "colorMap.h"

// In order to link dynamic library, please set path to it
// export LD_LIBRARY_PATH=<path to dynamic library>:$LD_LIBRARY_PATH

int main()
{

  for(auto p : ColorMap::get())
    p->colorInfo();

  return 0;
}
