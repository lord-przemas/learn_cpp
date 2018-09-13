#include "header.h"
#include <iostream>

void printVariable3()
{
  std::cout << "printVariable3(): variable_3 = " << variable_3 << std::endl;
}

int variable_4 { 4 };
const int variable_5 { 5 };

void printVariable4()
{
  std::cout << "printVariable4(): variable_4 = " << variable_4 << std::endl;
}

void printVariable5Address()
{
  std::cout << "printVariable5Address(): &variable_5 = " << &variable_5 << std::endl;
}

void externalLinkage2() {}

static void internalLinkage2() {}
void internalLinkage3() {}
// it's forbidden to declare function as static
// if it has been declared previosly as non-static
//static void internalLinkage4() {}
