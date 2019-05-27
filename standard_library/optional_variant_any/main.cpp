#include <iostream>
#include <optional>
#include <variant>
#include <any>
#include <memory>

class HeavyObject
{
  private:
    int number {777};

  public:
    HeavyObject() = default;
    HeavyObject(int num);

    int getNumber() const { return number; }
};

HeavyObject::HeavyObject(int num)
  : number {num}
{
}

std::optional<HeavyObject> createHeavyObject(bool notFail = true)
{
  return notFail ? std::make_optional<HeavyObject>(999) : std::nullopt;
  //  return {};
}

namespace my
{
  class any_interface
  {
    public:
      virtual void* get_p() = 0;
      virtual ~any_interface() = default;
  };

  template <typename T>
  class any_value : public any_interface
  {
    private:
      T value {};

    public:
      any_value(const T& t)
        : value {t} 
      {
      }

      void* get_p() override
      {
        return &value;
      }
  };

  class any
  {
    private:
      std::unique_ptr<any_interface> value {};

    public:
      template <typename T>
      any(const T& t)
      : value { std::make_unique<any_value<T> >(t) }
      {
      }

      template <typename T>
      void operator=(const T& t)
      {
        value = std::make_unique<any_value<T> >(t);
      }

      template <typename T>
      friend T any_cast(any& _any);
  };

  template <typename T>
  T any_cast(any& _any)
  {
    return *static_cast<T*>(_any.value->get_p());
  }
}

int main()
{

  std::cout << "---=== OPTIONAL ===---" << std::endl; 
  std::cout << "*** Not empty optional ***" << std::endl; 
  {
    //  std::optional<HeavyObject> optional1 {HeavyObject{12345}};
    std::optional<HeavyObject> optional1 {std::make_optional<HeavyObject>(12345)};

    if(!optional1.has_value())
    {
      std::cout << "optional1 is Empty!" << std::endl; 
    }
    std::cout << "Not empty: " << (*optional1).getNumber() << std::endl; 
    std::cout << "Not empty: " << optional1->getNumber() << std::endl; 
    std::cout << "Not empty: " << optional1.value().getNumber() << std::endl; 
    std::cout << "Not empty: " << optional1.value_or(-1).getNumber() << std::endl; 
    std::cout << std::endl; 
  }

  std::cout << "*** Empty optional ***" << std::endl; 
  {
    std::optional<HeavyObject> optional2 {};
    if(!optional2.has_value())
    {
      std::cout << "optional2 is Empty!" << std::endl; 
    }
    std::cout << "Empty: " << optional2.value_or(-1).getNumber() << std::endl; 
    std::cout << "Empty: " << (*optional2).getNumber() << std::endl; 
    std::cout << "Empty: " << optional2->getNumber() << std::endl; 

    try {
      std::cout << "Not empty: " << optional2.value().getNumber() << std::endl; 
    }
    catch(std::bad_optional_access boa) {
      std::cout << boa.what() << std::endl; 
    }
    std::cout << std::endl; 
  }

  std::cout << "*** Returning from function ***" << std::endl; 
  {
    auto isEmpty = [](const std::optional<HeavyObject>& opt) {
      if(opt.has_value()) {
        std::cout << "optional3 is NOT empty!" << std::endl; 
      }
      else {
        std::cout << "optional3 is empty!" << std::endl; 
      }
    };

    auto optional3 = createHeavyObject();
    isEmpty(optional3);

    optional3 = createHeavyObject(false);
    isEmpty(optional3);
  }


  std::cout << std::endl; 
  std::cout << "---=== VARIANT ===---" << std::endl; 
  {
    std::variant<int, float, std::string> variant1 {111};
    std::cout << "Value (int): " << std::get<int>(variant1) << std::endl;
    try {
      std::cout << "Value (float): " << std::get<float>(variant1) << std::endl;
    }
    catch(std::bad_variant_access bva) {
      std::cout << bva.what() << std::endl; 
    }

    std::get<int>(variant1) = 222;
    std::cout << "Value (int): " << std::get<int>(variant1) << std::endl;

    variant1.emplace<int>(333);
    std::cout << "Value (int): " << std::get<int>(variant1) << std::endl;

    variant1.emplace<0>(444);
    std::cout << "Value (int): " << std::get<int>(variant1) << std::endl;
    std::cout << "Index (int): " << variant1.index() << std::endl;

    variant1.emplace<std::string>("Lorem ipsum...");
    std::cout << "Value (std::string): " << std::get<std::string>(variant1) << std::endl;
    std::cout << "Index (std::string): " << variant1.index() << std::endl;
    try {
      std::cout << "Value (int): " << std::get<int>(variant1) << std::endl;
    }
    catch(std::bad_variant_access bva) {
      std::cout << bva.what() << std::endl; 
    }
  }


  std::cout << std::endl; 
  std::cout << "---=== ANY ===---" << std::endl; 
  {
    std::cout << std::boolalpha;

    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
    a = HeavyObject{789};
    std::cout << a.type().name() << ": " << std::any_cast<HeavyObject>(a).getNumber() << '\n';
    int x {234};
    a = x;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    std::cout << std::endl; 

    my::any b = 1;
    std::cout << "int: " << my::any_cast<int>(b) << '\n';
    b = 3.14;
    std::cout << "double: " << my::any_cast<double>(b) << '\n';
    b = true;
    std::cout << "bool: " << my::any_cast<bool>(b) << '\n';
    b = HeavyObject{789};
    std::cout << "HeavyObject: " << my::any_cast<HeavyObject>(b).getNumber() << '\n';
    b = x;
    std::cout << "int: " << my::any_cast<int>(b) << '\n';
  }

  return 0;
}
