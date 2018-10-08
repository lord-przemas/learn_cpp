#include <iostream>


class DelegatedConstructors
{
  private:
    int a;
    int b;

  public:
    DelegatedConstructors() : a(1), b(2){ }
    DelegatedConstructors(int x, int y) : a(x), b(y)
    {
      std::cout << "DelegatedConstructors(int x, int y)" << std::endl;
    }
    DelegatedConstructors(const DelegatedConstructors& dc) : DelegatedConstructors(dc.a, dc.b)
    {
      std::cout << "DelegatedConstructors(const DelegatedConstructors& dc)" << std::endl;
      // It only creates temporary object locally in scope of this constructor!
      DelegatedConstructors(123, 456);
    }

    void printNumbers() const
    {
      std::cout << "a: " << a << std::endl;
      std::cout << "b: " << b << std::endl;
    }
};


int main()
{

  DelegatedConstructors dc1;
  std::cout << "----------------------------------" << std::endl;

  DelegatedConstructors dc2(dc1);
  dc2.printNumbers();


  return 0;
}
