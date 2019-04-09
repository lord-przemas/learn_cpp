#include <iostream>

class ExplicitCtors 
{
  public:
    explicit ExplicitCtors(int x);
    explicit ExplicitCtors(const char* x);
    explicit ExplicitCtors(const ExplicitCtors& x);

};

ExplicitCtors::ExplicitCtors(int x)
{
  std::cout << "ExplicitCtors(int x)" << std::endl;
}
ExplicitCtors::ExplicitCtors(const char* x)
{
  std::cout << "ExplicitCtors(const char* x)" << std::endl;
}
ExplicitCtors::ExplicitCtors(const ExplicitCtors& x)
{
  std::cout << "ExplicitCtors(const ExplicitCtors& x)" << std::endl;
}

//**************************************************************

class ImplicitCtors
{
  public:
    ImplicitCtors(int x);
    ImplicitCtors(const char* x);

};

ImplicitCtors::ImplicitCtors(int x)
{
  std::cout << "ImplicitCtors(int x)" << std::endl;
}

ImplicitCtors::ImplicitCtors(const char* x)
{
  std::cout << "ImplicitCtors(const char* x)" << std::endl;
}

void takeImplicitCtors(ImplicitCtors ictors)
{
  std::cout << "takeImplicitCtors(ImplicitCtors ictors)" << std::endl;
}

class TakeImplicitCtors
{
  public:
    TakeImplicitCtors(ImplicitCtors ictors);
};

TakeImplicitCtors::TakeImplicitCtors(ImplicitCtors ictors)
{
  std::cout << "TakeImplicitCtors(ImplicitCtors ictors)" << std::endl;
}

//**************************************************************

int main()
{
  
//  ExplicitCtors ectors1 = 123;
//  ExplicitCtors ectors2 = "Hello World!";
//  ExplicitCtors ectors3 = ectors2;

  ExplicitCtors ectors4 { 123 };
  ExplicitCtors ectors5 { "Hello World!" };
  ExplicitCtors ectors6 { ectors5 };

  ExplicitCtors ectors7 = static_cast<ExplicitCtors>(123);
  ExplicitCtors ectors8 = static_cast<ExplicitCtors>("Hello World!");
  ExplicitCtors ectors9 = static_cast<ExplicitCtors>(ectors5);

  takeImplicitCtors(123);
  TakeImplicitCtors takeIctors1 {123};
  TakeImplicitCtors takeIctors2 {"Hello World!"};
//  TakeImplicitCtors takeIctors3 = 123;
//  TakeImplicitCtors takeIctors4 = "Hello World!";

  return 0;
}
