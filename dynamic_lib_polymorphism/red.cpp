#include <iostream>
#include "red.h"

const char* Red::colorName() const
{
  return "Blue";
}

void Red::colorInfo() const
{
  std::cout << "Red color is processing..." << std::endl;
}
