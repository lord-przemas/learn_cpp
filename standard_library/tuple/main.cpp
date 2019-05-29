#include <iostream>
#include <array>

class Qpa
{
  public:
    Qpa() = default;
    Qpa(const Qpa& qpa) {
      std::cout << "Copy Qpa!" << std::endl;
    }
    Qpa(Qpa&& qpa) {
      std::cout << "Move Qpa!" << std::endl;
    }
};

namespace mystd
{

  template<typename T, typename... Types>
  class tuple : public tuple<Types...>
  {
    private:
      T element;

    public:
      constexpr tuple(const T& t, const Types&... args)
      : element {t}, tuple<Types...>{args...}
      {
      }

      template<typename UT, typename... UTypes>
      constexpr tuple(UT&& t, UTypes&&... args)
      : element {std::forward<UT>(t)}, tuple<Types...>{ std::forward<UTypes>(args)...}
      {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if(std::is_lvalue_reference<UT&&>::value)
          std::cout << "UT is lvalue." << std::endl;
        if(std::is_rvalue_reference<UT&&>::value)
          std::cout << "UT is rvalue." << std::endl;
      }

      T get() const { return element; }
  };

  template<typename T>
  class tuple<T>
  {
    private:
      T element;

    public:
      constexpr tuple(const T& t)
      : element {t}
      {
      }

      template<typename UT>
      constexpr tuple(UT&& t)
      : element {t}
      {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if(std::is_lvalue_reference<UT&&>::value)
          std::cout << "UT is lvalue." << std::endl;
        if(std::is_rvalue_reference<UT&&>::value)
          std::cout << "UT is rvalue." << std::endl;
      }

      T get() const { return element; }
  };

  namespace v1
  {
    template<bool, typename T, typename... Types>
    class tuple_element_t
    {
      public:
        constexpr tuple_element_t(const tuple<T, Types...>& tup)
        {
        }
    };

    template<typename T, typename... Types>
    class tuple_element_t<true, T, Types...>
    {
      private:
        T element;

      public:
        using type = T;

        constexpr tuple_element_t(const tuple<T, Types...>& tup)
        : element {tup.get()}
        {
        }

        T get() const { return element; }
    };

    template<std::size_t A, std::size_t X,  typename T, typename... Types>
    class tuple_element_find : public tuple_element_find<A+1, X, Types...>, public tuple_element_t<A == X, T, Types...>
    {
      public:
        constexpr tuple_element_find(const tuple<T, Types...>& tup)
        : tuple_element_find<A+1, X, Types...> {tup},
          tuple_element_t<A == X, T, Types...> {tup}
        {
        }
    };

    template<std::size_t A, std::size_t X, typename T>
    class tuple_element_find<A,X,T> : public tuple_element_t<A == X, T>
    {};

    template<std::size_t I, typename = void>
    class tuple_element;

    template<std::size_t I, typename... Types>
    class tuple_element<I, tuple<Types...>> : public tuple_element_find<0, I, Types...>
    {
      public:
        constexpr tuple_element(const tuple<Types...>& tup)
        : tuple_element_find<0, I, Types...> {tup}
        {
        }
    };

    template< std::size_t I, class... Types >
    constexpr typename tuple_element<I, tuple<Types...> >::type
    get( const tuple<Types...>& t )
    {
      tuple_element<I, tuple<Types...>> element {t};
      return element.get();
    }

  }

  namespace v2
  {

    template <int Start, int End, typename T, typename... Types>
    struct tuple_element_impl;

    template <int Start, int End, typename T, typename... Types>
    struct tuple_element_impl<Start, End, tuple<T, Types...>>
    {
      using element_type = typename tuple_element_impl<Start+1, End, tuple<Types...>>::element_type;
      using tuple_type = typename tuple_element_impl<Start+1, End, tuple<Types...>>::tuple_type;
    };

    template <int End, typename T, typename... Types>
    struct tuple_element_impl<End, End, tuple<T, Types...>>
    {
      using element_type = T;
      using tuple_type = tuple<T, Types...>;
    };

    template <int I, typename... Types>
    struct tuple_element;

    template <int I, typename... Types>
    struct tuple_element<I, tuple<Types...>>
    {
      using element_type = typename tuple_element_impl<0, I, tuple<Types...>>::element_type;
      using tuple_type = typename tuple_element_impl<0, I, tuple<Types...>>::tuple_type;
      const element_type value {};

      tuple_element(const tuple<Types...>& t)
        : value {static_cast<const tuple_type&>(t).get()}
      {
      }
    };

    template< std::size_t I, class... Types >
    constexpr typename tuple_element<I, tuple<Types...> >::element_type
    get( const tuple<Types...>& t )
    {
      tuple_element<I, tuple<Types...>> element {t};
      return element.value;
    }

  }
}

template <typename T>
void checkType(T&& obj)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  typename std::remove_reference<T>::type lobj {std::forward<T>(obj)};
}

int main()
{

  int a {456};
  char b {'V'};
  double c {1.23456};

//  constexpr std::array<int, 3> arr {1,2,777};
//  constexpr my::tuple t {123, a, b, 'A', c, arr};
//  my::tuple t {123, a, b, 'A', c, std::string{"hello"}, 0};

  namespace my = mystd::v2;

  Qpa qpa {};
  mystd::tuple t {a, 3543, std::move(qpa), b, c, qpa};

  std::cout << std::endl;
  std::cout << my::get<0>(t) << std::endl;
  std::cout << my::get<1>(t) << std::endl;
//  std::cout << my::get<2>(t) << std::endl;
  std::cout << my::get<3>(t) << std::endl;
  std::cout << my::get<4>(t) << std::endl;
//  std::cout << my::get<5>(t) << std::endl;


  return 0;
}
