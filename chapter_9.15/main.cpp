#include <iostream>


class HeapWrapper
{
  public:
    HeapWrapper() {
      std::cout << "HeapWrapper()" << std::endl;
    }
    HeapWrapper(const HeapWrapper&) {
      std::cout << "HeapWrapper(const HeapWrapper&)" << std::endl;
    }
};

class ShallowCopy
{
  private:
    int a;
    double b;
    HeapWrapper c{};
};


int main()
{

  ShallowCopy src {};

  std::cout << "--------------" << std::endl;

  ShallowCopy dest { src };

  return 0;
}
