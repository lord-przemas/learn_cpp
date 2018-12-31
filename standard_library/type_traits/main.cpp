#include <iostream>
#include <typeinfo>

namespace my
{
  template <typename T1, typename T2> struct is_same { static constexpr bool value { false }; };
  template <typename T> struct is_same<T, T> { static constexpr bool value { true }; };

  template <typename T> struct is_integral { static constexpr bool value { false }; };
  template <> struct is_integral<int> { static constexpr bool value { true }; };
  template <> struct is_integral<unsigned int> { static constexpr bool value { true }; };
  template <> struct is_integral<short> { static constexpr bool value { true }; };
  template <> struct is_integral<unsigned short> { static constexpr bool value { true }; };

  template <typename T> struct is_array { static constexpr bool value { false }; };
  template <typename T> struct is_array<T[]> { static constexpr bool value { true }; };
  template <typename T, size_t N> struct is_array<T[N]> { static constexpr bool value { true }; };
}

class Test {};

template <
  typename T1, 
  typename T2, 
  bool = my::is_same<T1, T2>::value,
  bool = my::is_integral<T1>::value
  >
class Foo
{
  public:
    Foo(T1, T2)
    {
      std::cout << "Different types!" << std::endl;
    }
};

template <
  typename T1,
  typename T2
  >
class Foo<T1, T2, true, false>
{
  public:
    Foo(T1, T2)
    {
      std::cout << "Same non-integral types!" << std::endl;
    }
};

template <
  typename T1,
  typename T2
  >
class Foo<T1, T2, true, true>
{
  public:
    Foo(T1, T2)
    {
      std::cout << "Same integral types!" << std::endl;
    }
};


template <
  typename T1,
  typename T2
  >
class TypedefDeclaration
{
  public:
    typedef Foo<T1, T2> type;
};


template <
  typename T1,
  typename T2
  >
class TypedefUse
{
  public:
    typedef typename TypedefDeclaration<T1, T2>::type type;
    typename TypedefDeclaration<T1, T2>::type obj1;
    type obj2;
};

template <
  typename T1,
  typename T2,
  typename = typename TypedefDeclaration<T1, T2>::type
  >
class SpecTest
{
  public:
    SpecTest()
    {
      std::cout << "Common SpecTest!" << std::endl;
    }
};

template <
  typename T1,
  typename T2
  >
class SpecTest<T1, T2, Foo<int, int> >
{
  public:
    SpecTest()
    {
      std::cout << "Specialized SpecTest!" << std::endl;
    }
};

enum E {};

int main()
{
  int a;
  int b;
  float c;
  float d;
  Foo f1 {a, b};
  Foo f2 {a, c};
  Foo f3 {c, d};
  Foo<int, float> f4 {a, c};

  std::cout << std::endl;
  
  SpecTest<int, float> sp1 {};
  SpecTest<int, Test> sp2 {};
  SpecTest<int, int> sp3 {};

  std::cout << std::endl;
  
  std::cout << my::is_array<int>::value << std::endl;
  std::cout << my::is_array<int[]>::value << std::endl;
  std::cout << my::is_array<int[3]>::value << std::endl;

  std::cout << std::endl;

  return 0;
}
