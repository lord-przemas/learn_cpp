#include <iostream>


/*****************************************
 *           Friend functions            *
******************************************/
class Guys;

class Friends
{
  private:
    int a {123};
    double b {7.123};

    friend void printPrivateValues(const Friends& obj);
    friend Guys changeValues(Friends& obj);
};

class Guys
{
  private:
    int a {};
    double b {};

    void printValues() const;

    friend Guys changeValues(Friends& obj);
};

void Guys::printValues() const
{
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
}

void printPrivateValues(const Friends& obj)
{
  std::cout << "obj.a: " << obj.a << std::endl;
  std::cout << "obj.b: " << obj.b << std::endl;
  std::cout << std::endl;
}

// This function is a friend for two classes: Friends and Guys
Guys changeValues(Friends& obj)
{
  obj.a = 999;
  obj.b = 273.999;

  Guys guys{};
  guys.a = 11;
  guys.b = 22.345;

  return guys;
}

/*****************************************
 *           Friend classes              *
******************************************/

class Storage
{
  private:
    int a {0};
    int b {0};

    friend class Display;
};

class Display
{
  public:
    void setStorage(Storage& storage, int x, int y) const;
    void displayStorage(const Storage& storage) const;
};

void Display::setStorage(Storage& storage, int x, int y) const
{
  storage.a = x;
  storage.b = y;
}
void Display::displayStorage(const Storage& storage) const
{
  std::cout << "storage.a: " << storage.a << std::endl;
  std::cout << "storage.b: " << storage.b << std::endl;
}

/*****************************************
 *        Friend member functions        *
******************************************/
class Storage2;

class Display2
{
  public:
    void setStorage(Storage2& storage, int x, int y) const;
    void displayStorage(const Storage2& storage) const;
};

class Storage2
{
  private:
    int a {0};
    int b {0};

    friend void Display2::setStorage(Storage2& storage, int x, int y) const;
    friend void Display2::displayStorage(const Storage2& storage) const;
};

void Display2::setStorage(Storage2& storage, int x, int y) const
{
  storage.a = x;
  storage.b = y;
}
void Display2::displayStorage(const Storage2& storage) const
{
  std::cout << "storage.a: " << storage.a << std::endl;
  std::cout << "storage.b: " << storage.b << std::endl;
}

/*****************************************
 *                MAIN                   *
******************************************/
int main()
{

  Friends obj{};
  printPrivateValues(obj);
  Guys guys { changeValues(obj) };
  printPrivateValues(obj);

  Storage storage;
  Display display;
  display.setStorage(storage, 818, 242);
  display.displayStorage(storage);

  std::cout << std::endl;

  Storage2 storage2;
  Display2 display2;
  display2.setStorage(storage2, 666, 777);
  display2.displayStorage(storage2);


  return 0;
}
