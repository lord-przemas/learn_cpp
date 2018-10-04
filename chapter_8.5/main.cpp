#include <iostream>

class Members
{
  public:
    int a;
    int b;
};

class PublicMembers : public Members {};

class PrivateMembers : private Members {};

class AnyConstructor : protected Members
{
  public:
//  AnyConstructor(int,int) couses Default constructor to be removed,
//  so it has to be declared explicitly
//    AnyConstructor() = default;
    AnyConstructor(int x, int y) : Members{x, y} {}
};

class ImplicitConstructor : private Members
{
  public:
    ImplicitConstructor(int x = 1, int y = 2) : Members{x, y} {}
};

class ExplicitConstructor : private Members
{
  public:
    explicit ExplicitConstructor(int x = 1, int y = 2) : Members{x, y} {}
};

class ManyConstructors : private Members
{
  public:
    ManyConstructors(int x, int y) : Members{x ,y} {}
    // It's possible to call other constructor.
    ManyConstructors(const ManyConstructors& mc) : ManyConstructors{mc.a, mc.b} {}
};

class PrivateInheritance : private Members
{
  public:
//  Direct access to variables of base class is denied.
//    PrivateInheritance(const PrivateInheritance& mc) : a{mc.a}, b{mc.b} {}

//  But this one is possible. That's because a and b variables are initialize by default Constructor first.
    PrivateInheritance(const PrivateInheritance& mc) 
    { 
      a = mc.a; 
      b = mc.b;
    }
//  If you want to initialize a and b use any constructor from base class
//    PrivateInheritance(const PrivateInheritance& mc) : Members{mc.a, mc.b} {}
};

class PublicInheritance : public Members
{
  public:
//  Direct access to variables of base class is denied, even then they are publicly inherited.
//    PublicInheritance(const PublicInheritance& mc) : a{mc.a}, b{mc.b} {}

//  But this one is possible. That's because a and b variables are initialize by default Constructor first.
    PublicInheritance(const PublicInheritance& mc) 
    { 
      a = mc.a; 
      b = mc.b;
    }
//  If you want to initialize a and b use any constructor from base class
//    PublicInheritance(const PublicInheritance& mc) : Members{mc.a, mc.b} {}
};



int main()
{

  PublicMembers public1;
  PublicMembers public2 = {1, 2};
  PublicMembers public3 {3, 4};
  PublicMembers public4 {public3};
  public1 = public2;

  PrivateMembers private1;
//  PrivateMembers private2 = {1, 2}; // Copiler ERROR!
//  PrivateMembers private3 {3, 4};   // Copiler ERROR!
  PrivateMembers private4 {private1};
  private1 = private4;

//  AnyConstructor anyCtor1;          // Copiler ERROR! - Default constructor is removed
  AnyConstructor anyCtor2 = {1, 2};
  AnyConstructor anyCtor3 {3, 4};
  AnyConstructor anyCtor4 {anyCtor3};
  anyCtor2 = anyCtor3;

  ImplicitConstructor implicitCtor1;
  ImplicitConstructor implicitCtor2 = 123;

  ExplicitConstructor explicitCtor1;
//  ExplicitConstructor explicitCtor2 = 123;   // Copiler ERROR!
//  ExplicitConstructor explicitCtor3 = {123}; // Copiler ERROR!
  ExplicitConstructor explicitCtor4 {123};
  ExplicitConstructor explicitCtor5 {explicitCtor4};
  ExplicitConstructor explicitCtor6 = explicitCtor4;
  explicitCtor6 = explicitCtor4;
  


  return 0;
}
