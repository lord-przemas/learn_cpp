#include <iostream>

class BaseA
{
  private:
    void whoami() const { std::cout << "BaseA::whoami()" << std::endl; }
    virtual void whoamiVirt() const { std::cout << "BaseA::whoamiVirt()" << std::endl; }
};


class DerivedA : public BaseA
{
  public:
    void whoami() const { std::cout << "DerivedA::whoami()" << std::endl; }
    virtual void whoamiVirt() const override { std::cout << "DerivedA::whoamiVirt()" << std::endl; }
};

//******************************************************************
//******************************************************************

class BaseB
{
  public:
    void whoami() const { std::cout << "BaseB::whoami()" << std::endl; }
    virtual void whoamiVirt() const { std::cout << "BaseB::whoamiVirt()" << std::endl; }
};


class DerivedB : public BaseB
{
  private:
    void whoami() const { std::cout << "DerivedB::whoami()" << std::endl; }
    virtual void whoamiVirt() const override { std::cout << "DerivedB::whoamiVirt()" << std::endl; }
};

//******************************************************************
//******************************************************************

int main()
{

  BaseA baseA {};
  DerivedA derivedA {};

//  baseA.whoami();             // Comiler ERROR: private within this context
  derivedA.whoami();
//  derivedA.BaseA::whoami();   // Comiler ERROR: private within this context
  
  derivedA.whoamiVirt();
  BaseA* baseAptr { &derivedA };
//  baseAptr->whoamiVirt();     // Comiler ERROR: private within this context

  std::cout << "-----------------------" << std::endl;

  BaseB baseB {};
  DerivedB derivedB {};

  baseB.whoami();
//  derivedB.whoami();      // Comiler ERROR: private within this context
  derivedB.BaseB::whoami();
//  derivedB.whoamiVirt();  // Comiler ERROR: private within this context
  derivedB.BaseB::whoamiVirt();

  BaseB* baseBptr { &derivedB };
  baseBptr->whoamiVirt();

  std::cout << "-----------------------" << std::endl;


  return 0;
}
