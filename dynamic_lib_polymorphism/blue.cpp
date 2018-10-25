#include <iostream>
#include "blue.h"

const char* Blue::colorName() const
{
  return "Blue";
}

void Blue::colorInfo() const
{
  std::cout << "Blue color is processing..." << std::endl;
}
