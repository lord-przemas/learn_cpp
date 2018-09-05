#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>


void kindsOfArrays()
{
  int numbers1a[4] {1 ,2 ,3, 4}; // creates fixed array: {1, 2, 3, 4}
  int numbers2a[4] {1 ,2};       // creates fixed array: {1, 2, 0, 0}
  //int numbers3a[4] {1 ,2 ,3, 4, 5} ; // NOT OK! Amount of numbers exceeds fixed array length
  
  int numbers1b[] {1 ,2 ,3, 4}; // creates fixed array: {1, 2, 3, 4}
  int numbers2b[] {1 ,2};       // creates fixed array: {1, 2}
  int numbers3b[] {1 ,2 ,3, 4, 5} ; // fixed array length is deduced from initializer list

  int* numbers1c = new int[4] {1 ,2 ,3, 4}; // creates dynamic array: {1, 2, 3, 4}
  int* numbers2c = new int[4] {1 ,2};       // creates dynamic array: {1, 2, 0, 0}
//  int* numbers3c = new int[4] {1 ,2 ,3, 4, 5} ; // NOT OK! Amount of numbers exceeds dynamic array length

//  int* numbers1d = new int[] {1 ,2 ,3, 4}; // It's NOT OK! Length of dynamic array must be explicit
  for(int i {}; i < 4; ++i)
    std::cout << numbers2c[i] << std::endl;

  delete [] numbers1c;
  delete [] numbers2c;
}


/**********************************************/

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
  kindsOfArrays();
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
