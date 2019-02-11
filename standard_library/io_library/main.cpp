#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

template
< typename T1, 
  typename T2, 
  typename T3,
  typename T4 >
struct Data
{
  T1 a;
  T2 b;
  T3 c;
  T4 d;

  void print()
  {
    std::cout << "{ ";
    std::cout << a << ", ";
    std::cout << b << ", ";
    std::cout << c << ", ";
    std::cout << d;
    std::cout << " }" << std::endl;
  }
};


int main()
{
  {
    std::cout << "------------ std::basic_ostream -------------" << std::endl;

#define OSTRINGSTREAM

#ifdef OSTRINGSTREAM
    std::basic_ostringstream<char> os {};
#else // OFSTREAM
    std::basic_ofstream<char> os { "./file.txt" };
#endif

    //  std::basic_ostream<char> out { std::cout.rdbuf() };
    std::basic_ostream<char> out { os.rdbuf() };

    out << "basic_ostream output\n";
    out << "Hellow World!\n";
    out << "Hellow World!\n";
    out << "Hellow World!\n";
    out << "Hellow World!\n";
    out.put('a');
    out.put('\n');

    constexpr char text[] {"abcd 1234\n"};
    out.write(text, sizeof text);

    std::basic_ios<char>& oios { out };
    std::cout << std::boolalpha;
    std::cout << "-------------------------" << std::endl;
    std::cout << "good: " << oios.good() << std::endl;
    std::cout << "bad:  " << oios.bad() << std::endl;
    std::cout << "fail: " << oios.fail() << std::endl;
    std::cout << "eof:  " << oios.eof() << std::endl;

    std::cout << "[1] tellp:  " << out.tellp() << std::endl;
    out.seekp(15);
    std::cout << "[2] tellp:  " << out.tellp() << std::endl;
    out << "_TEXT_INSERTED_";
    std::cout << "[3] tellp:  " << out.tellp() << std::endl;
    out.seekp(-3, std::ios_base::end);
    std::cout << "[4] tellp:  " << out.tellp() << std::endl;
    out << "_TEXT_INSERTED_\n";
    std::cout << "[5] tellp:  " << out.tellp() << std::endl;

    std::cout << "-------------------------" << std::endl;
    std::cout << "good: " << oios.good() << std::endl;
    std::cout << "bad:  " << oios.bad() << std::endl;
    std::cout << "fail: " << oios.fail() << std::endl;
    std::cout << "eof:  " << oios.eof() << std::endl;

#ifdef OSTRINGSTREAM
    std::cout << '\n' << os.str() << std::endl;
#endif
  }


  {
    std::cout << "------------ std::basic_istream -------------" << std::endl;

#define ISTRINGSTREAM

#ifdef ISTRINGSTREAM
    std::string text { "Przemas 123 5.85 world end" };
    std::basic_istringstream<char> instream { text };
#else
    std::basic_ifstream<char> instream { "./ifstream_data.txt" };
#endif

    std::basic_istream<char> input { instream.rdbuf() };

    Data<std::string, int, double, char[10]> data { };
    input >> data.a;
    input >> data.b;
    input >> data.c;
    input >> data.d;
    data.print();

    input >> std::cout.rdbuf();
    std::cout << std::endl;
    std::cout << "-------------------------" << std::endl;

    input.seekg(0);
    std::cout << (char) input.peek() << std::endl;
    std::cout << (char) input.get() << std::endl;
    std::cout << (char) input.peek() << std::endl;
    std::cout << (char) input.get() << std::endl;
    std::cout << (char) input.peek() << std::endl;
    std::cout << (char) input.peek() << std::endl;
    std::cout << (char) input.peek() << std::endl;
    std::cout << (char) input.get() << std::endl;
    std::cout << (char) input.get() << std::endl;
    std::cout << (char) input.peek() << std::endl;
    if(input.unget())
      std::cout << (char) input.get() << std::endl;
    input.ignore(10);
    std::cout << (char) input.get() << std::endl;

  }

  return 0;
}
