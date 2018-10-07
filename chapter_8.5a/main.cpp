#include <iostream>


class ConstArray
{
  private:
    const int tbl[3];

  public:
//    ConstArray(){}  // error: uninitialized const member in ‘const int [3]’
//  Initialization of const array is only posible from C++11
    ConstArray() : tbl {1,2,3}
    {
    }
};

class A { public: A() { std::cout << "A()" << std::endl; } };
class B { public: B() { std::cout << "B()" << std::endl; } };
class C { public: C() { std::cout << "C()" << std::endl; } };
class D { public: D() { std::cout << "D()" << std::endl; } };

class InitializationOrder
{
  private:
    A a;
    B b;
    C c;
    D d;

  public:
    InitializationOrder() : a{}, b{}, c{}, d{} 
    { 
      std::cout << "InitializationOrder()" << std::endl << std::endl; 
    }
    
    InitializationOrder(int) : d{}, c{}, b{}, a{} 
    { 
      std::cout << "InitializationOrder()" << std::endl << std::endl; 
    }
};

int main()
{

  const int& cref1 ( 1.25 );
//  const int& cref2 { 1.25 };

  InitializationOrder initOrder1;
  InitializationOrder initOrder2 { 1 };


  return 0;
}
