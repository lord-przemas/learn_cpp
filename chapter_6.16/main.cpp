#include <iostream>
#include <vector>


int main()
{

  std::vector<int> vec1 {1, 2, 3, 4, 5, 6};
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl  << std::endl;

  vec1 = {11, 22};
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl  << std::endl;
  
  vec1 = {11, 22, 33, 44, 55, 66, 77};
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl  << std::endl;

  vec1[2] = 12345;     // access specified element
  vec1.at(3) = 12345;  // access specified element with bounds checking

  try
  {
    vec1.at(10) = 213; 
  }
  catch(std::out_of_range ex)
  {
    std::cout << "Out of range exception: "<< ex.what() << std::endl;
  }

  vec1.resize(12);
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl;
  for(auto element : vec1)
    std::cout << element << ", ";
  std::cout << std::endl << std::endl;
  
  vec1.reserve(50);
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl;
  for(auto element : vec1)
    std::cout << element << ", ";
  std::cout << std::endl << std::endl;

  vec1.resize(5);
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl;
  for(auto element : vec1)
    std::cout << element << ", ";
  std::cout << std::endl << std::endl;
  
  vec1.reserve(3); // if new capaciti is grater than current capacity, new storage is allocated, otherwise the method does nothing.
  std::cout << "size: "<< vec1.size() << std::endl;
  std::cout << "capacity: "<< vec1.capacity() << std::endl;
  for(auto element : vec1)
    std::cout << element << ", ";
  std::cout << std::endl << std::endl;


  return 0;
}
