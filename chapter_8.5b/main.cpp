#include <iostream>

class Inner
{
  private:
    int x;

  public:
    Inner() : x(0) {}
    Inner(int a) : x(a) {}
    int getValue() const { return x; }
};

class Outer
{
  private:
    // non-static data member initializers only available with -std=c++11 or -std=gnu++11
    int x = 123;
//    int b(2);          // the direct initialization form doesn’t work
    Inner inner = 456;
//    Inner inner2(123); // the direct initialization form doesn’t work
    
  public:
    Outer(){};
    Outer(int) : x() {};
    Outer(double) : inner() {};
    int getValue() const { return x; }
    const Inner& getInner() const { return inner; }
};

int main()
{

  Outer outer;
  std::cout << "outer.value: " << outer.getValue() << std::endl;
  std::cout << "inner.value: " << outer.getInner().getValue() << std::endl;

  Outer outer2(1);
  std::cout << "outer2.value: " << outer2.getValue() << std::endl;
  std::cout << "inner2.value: " << outer2.getInner().getValue() << std::endl;

  Outer outer3(1.2);
  std::cout << "outer3.value: " << outer3.getValue() << std::endl;
  std::cout << "inner3.value: " << outer3.getInner().getValue() << std::endl;


  return 0;
}
