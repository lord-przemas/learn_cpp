#include <iostream>
#include <functional>

extern "C" int func_asm(int,int);
extern "C" void call_func(void (*)(int, char));
extern "C" void call_func_2();

void test(int x, char c = 'x')
{
  std::cout << "Argument x = " << x << std::endl;
  std::cout << "Argument c = " << c << std::endl;
  std::cout << "-------------------------" << std::endl;
}


int main()
{

  void (*ptr1)(int, char) = test;  
//  void (*const ptr2)(int, char); // error: uninitialized const ‘ptr2’
  void (*const ptr2)(int, char) { test };
  std::function<void(int,char)> func_obj { test };


  test(0);
//  ptr1(1);       // error: too few arguments to function
  ptr1(1, 'g');    // implicit dereference
  (*ptr1)(2, 's'); // explicit dereference
  ptr2(3, 'h');
  func_obj(4, 'u');


  call_func_2();
  call_func(test);

  return 0;
}
