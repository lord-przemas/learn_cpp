#include <cstdio>

class This
{
  private:
    int number;

  public:
    This(int number)
//      : this->number {x}  // it's not allowed
    {
//      number = number;
      this->number = number;
    }

    int getNumber() const { return number; }
};

namespace dupa
{
  const class Cout
  {
    public:
      Cout() = default;
      const Cout& operator<<(const Cout& c) const;
      const Cout& operator<<(const char* text) const;
      const Cout& operator<<(char c) const;
      const Cout& operator<<(int num) const;
      const Cout& operator<<(double num) const;
  } cout, endl;
}

const dupa::Cout& dupa::Cout::operator<<(const Cout& c) const
{
  printf("\n");
  return *this;
}

const dupa::Cout& dupa::Cout::operator<<(const char* text) const
{
  printf("%s", text);
  return *this;
}

const dupa::Cout& dupa::Cout::operator<<(char c) const
{
  printf("%c", c);
  return *this;
}

const dupa::Cout& dupa::Cout::operator<<(int num) const
{
  printf("%d", num);
  return *this;
}

const dupa::Cout& dupa::Cout::operator<<(double num) const
{
  printf("%f", num);
  return *this;
}

int main()
{

  This t { 123456 };
  double x {1.2342};
  dupa::cout << "number: " << t.getNumber() << dupa::endl << "Hello World!" << dupa::endl << 'A' << dupa::endl;

  return 0;
}
