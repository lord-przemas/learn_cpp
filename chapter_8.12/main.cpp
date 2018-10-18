#include <iostream>


class StaticMembers
{
  public:
//    static int a {0}; // It's not allowed to initialize static non-const variable in class body
    static const int a;
    static const int b {1};
    static constexpr int c {2};
    static int d;
  
  private:
    static int e;
    int number{};

  public:
    void setE(int value) { e = value; }
    int getE() const { return e; }

    static void setEstatic(int value) { e = value; }
    static int getEstatic() { return e; }
    static void staticFoo();
};

const int StaticMembers::a {123};
//const int staticmembers::b {11}; // error: duplicate initialization of ‘staticmembers::b’

int StaticMembers::d {3};
int StaticMembers::e {}; // Static variable has to be initialized, otherwise "undefined reference" occurs.

void StaticMembers::staticFoo()
{
//  it's not permitted to change calue of non-static variable
//  in static member function
//  number = 10;
  d = 10;
}


class StaticConstructor
{
  private:
    static int a;
    static int b;
    
    static class Init
    {
      public:
        Init();
    } init;

  public:
    static void printValues();
};

int StaticConstructor::a {};
int StaticConstructor::b {};
StaticConstructor::Init StaticConstructor::init {};

StaticConstructor::Init::Init() 
{
  std::cout << "StaticConstructor::Init::Init()" << std::endl;
  a = 123;
  b = 456;
}

void StaticConstructor::printValues()
{
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
}


int main()
{

  StaticMembers obj{};

  StaticMembers::setEstatic(444);
  std::cout << "Value: " << obj.getE() << std::endl; 

  obj.setE(777);
  std::cout << "Value: " << StaticMembers::getEstatic() << std::endl; 


  StaticConstructor::printValues();

  return 0;
}
