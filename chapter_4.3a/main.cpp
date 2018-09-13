#include <iostream>
#include "header.h"

extern int value_1;         // OK! - external linkage
//int value_1 { 111 };        // ERROR! - multiple definition of `value_1'
//const int value_1 { 111 };  // OK! - internal linkage
//static int value_1 { 111 }; // OK! - internal linkage

extern int value_2;         // OK! - external linkage
//int value_2 { 222 };        // ERROR! - multiple definition of `value_2'
//const int value_2 { 222 };  // OK! - internal linkage
//static int value_2 { 222 }; // OK! - internal linkage

//extern const int value_3;   // ERROR! - undefined reference to `value_3'
int value_3 { 333 };        // OK! - external linkage
//const int value_3 { 333 };  // OK! - internal linkage
//static int value_3 { 333 }; // OK! - internal linkage

extern const int value_4;   // OK! - external linkage
//int value_4 { 444 };        // ERROR! - multiple definition of `value_4'
//const int value_4 { 444};   // OK! - internal linkage
//static int value_4 { 444 }; // OK! - internal linkage




int main()
{

  std::cout << "value_1: " << value_1 << std::endl;
  std::cout << "value_2: " << value_2 << std::endl;
  std::cout << "value_3: " << value_3 << std::endl;
  std::cout << "value_4: " << value_4 << std::endl;
  
  std::cout << "------------------------------" << std::endl;
  std::cout << "main(): variable_3 = " << variable_3 << std::endl;
  printVariable3();
  variable_3 = 123456;
  std::cout << "main(): variable_3 = " << variable_3 << std::endl;
  printVariable3();
  std::cout << "------------------------------" << std::endl;
  std::cout << "main(): variable_4 = " << variable_4 << std::endl;
  printVariable4();
  variable_4 = 123456;
  std::cout << "main(): variable_4 = " << variable_4 << std::endl;
  printVariable4();
  std::cout << "------------------------------" << std::endl;
  std::cout << "main(): &variable_5 = " << &variable_5 << std::endl;
  printVariable5Address();
  
  internalLinkage1();
//  internalLinkage2();
//  internalLinkage3();
//  internalLinkage4();



  return 0;
}
