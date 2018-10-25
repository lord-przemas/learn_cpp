#ifndef COLOR_H
#define COLOR_H

class Color
{
  public:
    virtual const char* colorName() const = 0;
    virtual void colorInfo() const = 0;
};

#endif //COLOR_H
