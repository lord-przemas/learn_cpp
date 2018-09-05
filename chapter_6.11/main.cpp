#include <iostream>

void referenceToArray(int (&arr) [3])
{
  std::cout << "arr size: " << sizeof(arr) << std::endl;
}
void pointerToArray(int *arr)
{
//  std::cout << "arr size: " << sizeof(arr) << std::endl;
}

class Test {};

int main()
{

  int value {1234};
  
  int& ref1a {value};
  int& ref2a {ref1a};
//  int& ref3a {123}; // Compile ERROR! We cannot bind r-value to non-const reference.
//  int& ref4a = 123; // Compile ERROR! We cannot bind r-value to non-const reference.
  std::cout << &value << std::endl;
  std::cout << &ref1a << std::endl;
  std::cout << &ref2a << std::endl << std::endl;

  const int& ref1b {value};
  const int& ref2b {ref1a};
  const int& ref3b {ref2b};
  const int& ref4b {123}; // It's OK! It's allowed to bind r-value to const reference.
  const int& ref5b = 123; // It's OK! It's allowed to bind r-value to const reference.
  
  std::cout << &value << std::endl;
  std::cout << &ref1b << std::endl;
  std::cout << &ref2b << std::endl;
  std::cout << &ref3b << std::endl << std::endl;

  int&& rref {123 + 7};
  int& ref1c {rref};
//  int& ref2c {123 + 7};     // Compile ERROR! We cannot bind r-value to non-const reference.
  const int& ref3c {123 + 7}; // It's OK! It's allowed to bind r-value to const reference.

//  Test& refTest1 { Test{} };     // Compile ERROR! We cannot bind r-value to non-const reference.
  const Test& refTest2 { Test{} }; // It's OK! It's allowed to bind r-value to const reference.

  int tbl1[3] {1,2,3};
  int tbl2[2];
  int tbl3[4];
  referenceToArray(tbl1);
//  referenceToArray(tbl2); // Compile ERROR!
//  referenceToArray(tbl3); // Compile ERROR!

// Note: There is no difference between reference to array
// and pointer to array from assembly code persperctive
// It's only a difference in compilation process
  pointerToArray(tbl1);

  return 0;
}
