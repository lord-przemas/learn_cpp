#include <iostream>
#include <type_traits>

class Base {};
class Derived : public Base {};
class AnyObject {};

template <typename T, typename = void>
class ObjectWrapper
{
  public:
    ObjectWrapper(const T& obj)
    {
      std::cout << "Any object!" << std::endl;
    }
};

template <typename T>
class ObjectWrapper<T, std::enable_if_t<std::is_class<T>::value && std::is_base_of<Base, T>::value>>
{
  public:
    ObjectWrapper(const T& obj)
    {
      std::cout << "Base object!" << std::endl;
    }

    template <typename Tp>
    ObjectWrapper(const Tp& obj)
    {
      static_assert(std::is_base_of<Base, Tp>::value, "ERROR: Argument is not derived from Base class!");
      std::cout << "Derived object!" << std::endl;
    }
};

template <typename T>
class ObjectWrapper<T, std::enable_if_t<std::is_integral<T>::value>>
{
  public:
    ObjectWrapper(const T& obj)
    {
      std::cout << "Integral type!" << std::endl;
    }
};

int main()
{
  Base base {};
  Derived derived {};
  AnyObject anyObject {};

  ObjectWrapper<Base> ow1 {base};
  ObjectWrapper ow2 {derived};
  ObjectWrapper<Base> ow3 {derived};
  ObjectWrapper<int> ow4 {345346};
  ObjectWrapper ow5 {34.5346};
//  ObjectWrapper<Base> ow6 {34.5346};


  return 0;
}

