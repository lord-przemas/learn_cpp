#include <iostream>

class ConstFunctions
{
  private:
    int number;
    mutable int changable {1};
    int tbl[10];

  public:
    ConstFunctions(int x);
    void constFoo() const;
    void constFooChangeMutable() const;
    void nonConstFoo();
    int getNumber() const { return number; }
    int getChangable() const { return changable; }

    int& operator[](int i) { return tbl[i]; }
    const int& operator[](int i) const { return tbl[i]; }
};

ConstFunctions::ConstFunctions(int x)
{
  number = x;
  constFoo();
  // Constructor can call non-const member function beacause it can modify member variables
  nonConstFoo();
}

void ConstFunctions::constFoo() const
{
//  nonConstFoo(); // Compiler ERROR: const member function cannot call non-const member function
//  number = 44; // Compiler ERROR: const member function cannot change member variables
}
void ConstFunctions::constFooChangeMutable() const
{
  changable = 444;
}

void ConstFunctions::nonConstFoo()
{
  number = 999;
  constFoo();
}

int main()
{

  const ConstFunctions obj {123};
  std::cout << "Number: " << obj.getNumber() << std::endl;
  std::cout << "changable: " << obj.getChangable() << std::endl;
  obj.constFooChangeMutable();
  std::cout << "changable: " << obj.getChangable() << std::endl;

  ConstFunctions obj2 {666};
  const ConstFunctions& constRef = obj2;
//  constRef.nonConstFoo(); // Compiler ERROR: Object is treated as const object

  obj2[0] = 1234;
  // Below example would be not possible without oveloading a const operator[]
  std::cout << "tbl[0]: " << constRef[0] << std::endl;


  return 0;
}
