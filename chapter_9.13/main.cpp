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


  return 0;
}
