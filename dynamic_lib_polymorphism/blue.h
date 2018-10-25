#ifndef BLUE_H
#define BLUE_H
#include "color.h"

class Blue : public Color
{
  public:
    virtual const char* colorName() const;
    virtual void colorInfo() const;
};

#endif // BLUE_H
