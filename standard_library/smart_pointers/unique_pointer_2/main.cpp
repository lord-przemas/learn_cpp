#include <iostream>
#include <memory>

/*********************************************
                 OBJECT A                    *
**********************************************/

class A
{
  private:
    int _id {};
  public:
  A(int id);
  ~A();
};

A::A(int id)
  : _id {id}
{
  std::cout << "A::A( " << id  << " )" << std::endl;
}

A::~A()
{
  std::cout << "A::~A( " << _id  << " )" << std::endl;
}

/*********************************************
                   MAIN                      *
**********************************************/
int main()
{
  std::cout << "-------- 1 ---------" << std::endl;
  {
    std::unique_ptr<A> p1 {};
    std::unique_ptr<A> p2 {nullptr};
    std::cout << "........" << std::endl;
  }
  std::cout << "-------- 2 ---------" << std::endl;
  {
    std::unique_ptr<A> p3 {new A{21}};
    std::unique_ptr<A> p4 {std::make_unique<A>(22)};
    p4 = std::make_unique<A>(23);
    std::cout << "........" << std::endl;
  }
  std::cout << "-------- 3 ---------" << std::endl;
  {
    std::unique_ptr<A> p5 {std::make_unique<A>(31)};
    p5.reset(new A{32});
//    p5.reset(std::make_unique<A>(31)); // error: no matching function for call  
    std::cout << "........" << std::endl;
  }
  std::cout << "-------- 4 ---------" << std::endl;
  {
    std::unique_ptr<A> p6 {std::make_unique<A>(41)};
//    std::unique_ptr<A> p7 { p6 }; // error: use of deleted function
    std::unique_ptr<A> p7 { std::move(p6) };
    std::cout << "........" << std::endl;
  }
  std::cout << "-------- 5 ---------" << std::endl;
  {
    std::unique_ptr<A> p8 {std::make_unique<A>(51)};
    std::unique_ptr<A> p9 {std::make_unique<A>(52)};
    std::unique_ptr<A> p10 {std::make_unique<A>(53)};
    p10 = std::move(p8);
//    p10.reset(p9.get()); // Runtime Error
    p10.reset(p9.release());
    std::cout << "........" << std::endl;
  }
  std::cout << "-------- END --------" << std::endl;

  return 0;
}
