#include <iostream>


namespace TC1
{
  void foo(int x);
}
namespace TC2
{
  void foo(int x);
  void foo(short x);
}
namespace TC3
{
  void foo(int x);
  void foo(int* x);
}
namespace TC4
{
  void foo(int x);
  void foo(char& x);
}
namespace TC5
{
  void foo(int x);
  void foo(char& x);
  void foo(const char& x);
}
namespace TC6
{
  void foo(char& x);
  void foo(const char& x);
}
namespace TC7
{
  void foo(char x);
  void foo(char& x);
  void foo(const char& x);
  void foo(char&& x);
}
namespace TC8
{
  void foo(int x);
  void foo(char* x);
  void foo(void* x);
}
namespace TC9
{
  void foo(char x);
  void foo(short x);
}
namespace TC10
{
  void foo(int* p);
  void foo(int** pp);
}

int main()
{

  char c {1};
  short s {2};
  int i {3};

  TC1::foo(c);
  TC1::foo('a');

  TC2::foo(c);

  TC3::foo(c);
  TC3::foo(0);
  TC3::foo(nullptr);

  TC4::foo(c);
  TC4::foo(123);

  TC5::foo(c);
  TC5::foo('a');
  TC5::foo(123);
  TC5::foo(static_cast<char>(123));

  TC6::foo(c);
  TC6::foo(123);

//  TC7::foo(c);    // compile ERROR! - call of overloaded ‘foo(char&)’ is ambiguous
//  TC7::foo(123);  // compile ERROR! - call of overloaded ‘foo(char&)’ is ambiguous
  
  TC8::foo(0);
//  TC8::foo(nullptr); // Compile ERROR! - call of overloaded ‘foo(std::nullptr_t)’ is ambiguous
  TC8::foo(&c);
  TC8::foo(&i);

  TC9::foo(s);
//  TC9::foo(i);  // Compile ERROR! - call of overloaded ‘foo(int&)’ is ambiguous

  TC10::foo(&i);
//  TC10::foo(0);        // Compile ERROR! - call of overloaded ‘foo(int)’ is ambiguous
//  TC10::foo(nullptr);  // Compile ERROR! - call of overloaded ‘foo(std::nullptr_t)’ is ambiguous


  return 0;
}



void TC1::foo(int x)
{
  std::cout << "TC1::foo(int x); x = " << (int) x << std::endl;
}

void TC2::foo(int x)
{
  std::cout << "TC2::foo(int x); x = " << (int) x << std::endl;
}

void TC2::foo(short x)
{
  std::cout << "TC2::foo(short x); x = " << (int) x << std::endl;
}

void TC3::foo(int x)
{
  std::cout << "TC3::foo(int x); x = " << (int) x << std::endl;
}
void TC3::foo(int* x)
{
  std::cout << "TC3::foo(int* x); x = " << (uint64_t) x << std::endl;
}

void TC4::foo(int x)
{
  std::cout << "TC4::foo(int x); x = " << (int) x << std::endl;
}
void TC4::foo(char& x)
{
  std::cout << "TC4::foo(char& x); x = " << (int) x << std::endl;
}
void TC5::foo(int x)
{
  std::cout << "TC5::foo(int x); x = " << (int) x << std::endl;
}
void TC5::foo(char& x)
{
  std::cout << "TC5::foo(char& x); x = " << (int) x << std::endl;
}
void TC5::foo(const char& x)
{
  std::cout << "TC5::foo(const char& x); x = " << (int) x << std::endl;
}
void TC6::foo(char& x)
{
  std::cout << "TC6::foo(char& x); x = " << (int) x << std::endl;
}
void TC6::foo(const char& x)
{
  std::cout << "TC6::foo(const char& x); x = " << (int) x << std::endl;
}
void TC7::foo(char x)
{
  std::cout << "TC7::foo(char x); x = " << (int) x << std::endl;
}
void TC7::foo(char& x)
{
  std::cout << "TC7::foo(char& x); x = " << (int) x << std::endl;
}
void TC7::foo(const char& x)
{
  std::cout << "TC7::foo(const char& x); x = " << (int) x << std::endl;
}
void TC7::foo(char&& x)
{
  std::cout << "TC7::foo(char&& x); x = " << (int) x << std::endl;
}
void TC8::foo(int x)
{
  std::cout << "TC8::foo(int x); x = " << (int) x << std::endl;
}
void TC8::foo(char* x)
{
  std::cout << "TC8::foo(char* x); x = " << (uint64_t) x << std::endl;
}
void TC8::foo(void* x)
{
  std::cout << "TC8::foo(void* x); x = " << (uint64_t) x << std::endl;
}
void TC9::foo(char x)
{
  std::cout << "TC9::foo(char x); x = " << (int) x << std::endl;
}
void TC9::foo(short x)
{
  std::cout << "TC9::foo(short x); x = " << (int) x << std::endl;
}
void TC10::foo(int* p)
{
  std::cout << "TC10::foo(int* p); p = " << (uint64_t) p << std::endl;
}
void TC10::foo(int** pp)
{
  std::cout << "TC10::foo(int** pp); pp = " << (uint64_t) pp << std::endl;
}
