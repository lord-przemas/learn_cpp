#ifndef RED_H
#define RED_H
#include "color.h"

class Red : public Color
{
  public:
    virtual const char* colorName() const;
    virtual void colorInfo() const;
};

#endif // RED_H
