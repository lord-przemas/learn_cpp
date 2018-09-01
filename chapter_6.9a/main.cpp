#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

class HeavyObject
{
  public:
    HeavyObject();
    HeavyObject(const HeavyObject& obj);
    ~HeavyObject();
    void operator=(const HeavyObject& obj);
};

HeavyObject::HeavyObject()
{
  std::cout << "Default Constructor!" << std::endl;
}
HeavyObject::HeavyObject(const HeavyObject& obj)
{
  std::cout << "Copy Constructor!" << std::endl;
}
HeavyObject::~HeavyObject()
{
  std::cout << "Destructor!" << std::endl;
}
void HeavyObject::operator=(const HeavyObject& obj)
{
  std::cout << "Copy assignment!" << std::endl;
}

int main()
{
// Calls only Copy assignement on all objects in table

  const unsigned int SIZE = 3;
  char* buffer = new char[SIZE * sizeof(HeavyObject)];
  auto* objs = reinterpret_cast<HeavyObject*>(buffer);
  HeavyObject ho;
  for ( unsigned int i = 0; i < SIZE; ++i )
  {
    objs[i] = ho;
  }

  delete [] buffer;


// Calls Copy assignement and Destructors
// on all objects in table
  std::cout << "------------------" << std::endl;
  std::vector<HeavyObject> v;
  v.reserve(10);
  v.push_back(ho);
  v.push_back(ho);
  v.push_back(ho);
  std::cout << "------------------" << std::endl;

// Calls Default constructor, Copy assignement and Destructors
// on all objects in table
//
//  const unsigned int SIZE = 3;
//  auto* objs = new HeavyObject[SIZE];
//  HeavyObject ho;
//  for ( unsigned int i = 0; i < SIZE; ++i )
//  {
//    objs[i] = ho;
//  }
//
//  delete [] objs;


  return 0;
}
