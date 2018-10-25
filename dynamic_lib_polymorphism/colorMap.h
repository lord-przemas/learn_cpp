#ifndef COLOR_MAP_H
#define COLOR_MAP_H

#include <memory>
#include <vector>
#include "color.h"


class ColorMap
{
  public:
    static const std::vector<std::shared_ptr<Color> >& get() { return colors; }

  private:
    static const std::vector<std::shared_ptr<Color> > colors; 

    ColorMap() = delete;
};

#endif //COLOR_MAP_H
