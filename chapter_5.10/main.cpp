#include <iostream>


void cinBasics()
{
  int x;
  std::cin >> x;
  std::cout << x << std::endl;

  char text[20];
  std::cin >> text;
  std::cout << text << std::endl;
  
  float z;
  std::cin >> z;
  std::cout << z << std::endl;
}

void cinIgnore()
{
  int x;
  std::cin >> x;
  std::cin.ignore(64, '\n');
  std::cout << x << std::endl;
  
  char text[20];
  std::cin >> text;
  std::cout << text << std::endl;
}

void cinFail()
{
  while(true)
  {
    short x;
    std::cin >> x;
    std::cout << x << std::endl;
  
    if(std::cin.fail())
    {
      std::cout << "Extraction failed!" << std::endl;
      std::cin.clear();
      std::cin.ignore(128, '\n');
    }
    else
    {
      return;
    }
  }
}

int main()
{
 
//  cinBasics();
//  cinIgnore();
  cinFail();

  return 0;
}
