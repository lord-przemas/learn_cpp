#include <iostream>


class Object {};

int operator+(const Object& a, int b) { return 123; }
Object operator+(int a, const Object& b) { return Object{}; }
// At least one of the operands in an overloaded operator must be a user-defined type.
// int operator+(int a, int b) { return 123; }

class Operators
{
  public:
    Operators operator-(const Operators& o) const
    {
      std::cout << "Operators::operator-(const Operators& o)" << std::endl;
      return Operators{};
    }

    Operators operator-() const
    {
      std::cout << "Operators::operator-()" << std::endl;
      return Operators{};
    }

    bool operator!() const { return true; }
};


int main()
{

  Operators op1;
  Operators op2 = -op1;
  op1 - op2;

  if(!op1)
    std::cout << "op1 == true" << std::endl;


  return 0;
}
