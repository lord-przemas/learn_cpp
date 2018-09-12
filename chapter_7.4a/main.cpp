#include <iostream>


int returnByValue()
{
  int x {123};
  return x;
}

int* returnByAddress1()
{
  int x {123};
  return &x;
}

int& returnByReference1()
{
  int x {123};
  return x;
}

const int& returnByReference2()
{
  return 123;
}


int& returnRefToStatic()
{
  static int value {123456789};
  return value;
}

int main()
{

  // binding the r-value reference to the const reference extends 
  // the lifetime of returned copy to the lifetime of value1 reference
  const int& value1 { returnByValue() };
  // binding the reference of local variable leads to runtime error
  const int& value2 { returnByReference1() };
  // It doesn't work
  const int& value3 { returnByReference2() };
  
  
  std::cout << value1 << std::endl;
//  std::cout << value2 << std::endl; // runtime ERROR!
//  std::cout << value3 << std::endl; // runtime ERROR!

  std::cout << "--------------------------" << std::endl;
  std::cout << returnRefToStatic() << std::endl;
  returnRefToStatic() = 55;
  std::cout << returnRefToStatic() << std::endl;

  return 0;
}
