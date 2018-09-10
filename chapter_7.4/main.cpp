#include <iostream>



void passByPointer1(int* ptr)
{
  std::cout << "------ passByPointer1 ------" << std::endl;
  *ptr = 999;
  ptr = nullptr;
}

void passByPointer2(const int* ptr)
{
  std::cout << "------ passByPointer2 ------" << std::endl;
//  *ptr = 999;
  ptr = nullptr;
}

void passByPointer3(int* &ptr)
{
  std::cout << "------ passByPointer3 ------" << std::endl;
  *ptr = 999;
  ptr = nullptr;
}

void passByPointer4(const int* &ptr)
{
  std::cout << "------ passByPointer4 ------" << std::endl;
//  *ptr = 999;
  ptr = nullptr;
}

void passByPointer5(int* const &ptr)
{
  std::cout << "------ passByPointer5 ------" << std::endl;
  *ptr = 999;
//  ptr = nullptr;
}

void passByPointer6(const int* const &ptr)
{
  std::cout << "------ passByPointer6 ------" << std::endl;
//  *ptr = 999;
//  ptr = nullptr;
}

template <typename T>
void verifyFunction(void (*func)(T))
{
  std::cout << "*******************************" << std::endl;
  int number {123};
  int* ptr {&number};
  std::cout << "Value: " << number << std::endl;
  func(ptr);
  std::cout << "Value: " << number << std::endl;
  std::cout << "Pointer: " << ptr << std::endl << std::endl;
}


template <>
void verifyFunction<const int*&>(void (*func)(const int* &ptr))
{
  std::cout << "*******************************" << std::endl;
  int number {123};
  const int* ptr {&number};
  std::cout << "Value: " << number << std::endl;
  func(ptr);
  std::cout << "Value: " << number << std::endl;
  std::cout << "Pointer: " << ptr << std::endl << std::endl;
}

int main()
{

  verifyFunction(passByPointer1);
  verifyFunction(passByPointer2);
  verifyFunction(passByPointer3);
  verifyFunction(passByPointer4);
  verifyFunction(passByPointer5);
  verifyFunction(passByPointer6);

  return 0;
}
