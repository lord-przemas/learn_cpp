#include <iostream>


int main()
{

  int tbl[] {1, 2, 3, 4};
  void* ptr { tbl };

  std::cout << ptr << std::endl;

// ISO C++ forbids pointer arithmetic, however some copilers allow
// to compile such code as below f.e. GCC allows to compile this code, 
// but clang produces compiler error)
  ptr++;
  std::cout << ptr << std::endl;
  ptr = ptr + 1;
  std::cout << ptr << std::endl;
  std::cout << *static_cast<int*>(ptr + 2) << std::endl;


  return 0;
}
