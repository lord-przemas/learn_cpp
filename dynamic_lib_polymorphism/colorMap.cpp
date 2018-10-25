#include "colorMap.h"
#include "red.h"
#include "blue.h"

const std::vector<std::shared_ptr<Color> > ColorMap::colors {
  std::make_shared<Red>(),
  std::make_shared<Blue>()
};

