#include <iostream>
#include <functional>

struct Test
{
  int num {1};
  int add(int a, int b) const
  {
    return a + b + num;
  }
  int operator()(int a, int b) const
  {
    return a + b + num;
  }
  Test() = default;
  Test(int x) : num {x} {}
};

int add(int a, int b)
{
  return a + b;
}

namespace my
{
  template <typename F, typename... Args>
  auto bind(F&& f, Args&&... args)
  {
    return [&f, &args...](){
      return f(args...);
    };
  }

  template <typename>
  class function;

  template <typename R, typename... Args>
  class function<R(Args...)>
  {
    private:
      using Signature = R(*)(Args...);
      Signature function_ptr;

    public:
      function(Signature signature)
        : function_ptr {signature}
      {
      }

    R operator()(Args... args)
    {
      return function_ptr(args...);
    }
  };

}

int main()
{
  int x {32};
  my::function<int(int, int)> my_foo {add};
  std::cout << "My function: " << my_foo(5, x) << std::endl;

//  my::function<int(const Test&, int, int)> my_method {&Test::add};
//  std::cout << "My method: " << my_foo(8, x) << std::endl;


  std::function<int(int,int)> f_add { add };
  std::cout << "f_add: " << f_add(11, 22) << std::endl;

  using Type = int (Test::*)(int,int) const;
  Type foo {&Test::add};
  Test test {};
  std::cout << "foo: " << (test.*foo)(11, 22) << std::endl;

  std::function<int(const Test&, int, int)> f_test_add { &Test::add };
  std::cout << "f_test_add: " << f_test_add(test, 11, 22) << std::endl;
  std::cout << "f_test_add: " << f_test_add(100, 11, 22) << std::endl;

  test.num = 345;
  std::function<int(const Test&)> f_class_member { &Test::num };
  std::cout << "f_class_member: " << f_class_member(test) << std::endl;

  std::function<int()> f_bind_add_1 { std::bind(add, 12, 18) };
  std::cout << "f_bind_add_1: " << f_bind_add_1() << std::endl;

  std::function<int(int)> f_bind_add_2 { std::bind(add, 5, std::placeholders::_1) };
  std::cout << "f_bind_add_2: " << f_bind_add_2(45) << std::endl;



  return 0;
}
