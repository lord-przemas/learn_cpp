#include <iostream>


class Object 
{
  public:
    Object() { std::cout << "Object()" << std::endl; }
    Object(const Object& obj) { std::cout << "Object(const Object& obj)" << std::endl; }
};

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

class TypeCast
{
  private:
    int number {};

  public:
    TypeCast(int x) : number{x}{}
    operator int() const { return number; }
    operator Object() const { 
      std::cout << "operator Object()" << std::endl;
      return Object{}; 
    }
};

class Cents
{
  private:
    int m_cents {};

  public:
    Cents(int cents) : m_cents {cents} {}
    
    friend void printCents(const Cents& cents);
};


void printCents(const Cents& cents)
{
  std::cout << "Cents: " << cents.m_cents << std::endl;
}

class Dollars
{
  private:
    int m_dollars {};

  public:
    Dollars(int dollars) : m_dollars {dollars} {}
    operator Cents() const { return Cents{m_dollars*100}; }
};

int main()
{

  Operators op1;
  Operators op2 = -op1;
  op1 - op2;

  if(!op1)
    std::cout << "op1 == true" << std::endl;

  std::cout << std::endl;

  TypeCast obj = 777;
  int number { obj };
  std::cout << "Number: " << number << std::endl;

  Object chuj =  obj;
  
  std::cout << std::endl;

  Dollars dollars {12};
  printCents(dollars);

  return 0;
}
