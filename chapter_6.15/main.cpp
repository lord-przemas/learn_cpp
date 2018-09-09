#include <iostream>

class FixedArrayException{};

template <typename T, size_t SIZE>
class FixedArray
{
  private:
    T fixedArray[SIZE] {};
  
  public:
    FixedArray() = delete;
    FixedArray(const FixedArray&) = delete;
    FixedArray(std::initializer_list<T> li);

    T& operator[](int index) const { return fixedArray[index]; }
    T* begin() { return fixedArray; }
    T* end() { return fixedArray + SIZE; }
    const T* cbegin() const { return fixedArray; }
    const T* cend() const { return fixedArray + SIZE; }
    constexpr size_t size() const { return SIZE; };
};

template <typename T, size_t SIZE>
FixedArray<T,SIZE>::FixedArray(std::initializer_list<T> li)
{
  if(li.size() <= SIZE)
  {
    int index {};
    for (const auto& element : li)
    {
      fixedArray[index++] = element;
    }
  }
  else
  {
    throw FixedArrayException {};
  }
}

// It's not possible to get array length even in this way
template <typename T>
void printArrayLength(T &tbl)
{
  std::cout << "Array length: " << sizeof(tbl) << std::endl;
  std::cout << "Array length: " << sizeof(T) << std::endl;
  std::cout << "Array length: " << sizeof(tbl) / sizeof(T) << std::endl << std::endl;
}

int main()
{
  int tbl[10];
  printArrayLength(tbl);
  
  double tbl2[54];
  printArrayLength(tbl2);

  try
  {
    FixedArray<int, 10> arr {1,2,3,4};
    for(auto& element : arr)
    {
      std::cout << element << std::endl;
    }
    std::cout << "FixedArray length: " << sizeof(arr) << std::endl;
    std::cout << "FixedArray length: " << arr.size() << std::endl;
  }
  catch(FixedArrayException ex)
  {
    std::cout << "Exception has been thrown!" << std::endl;
    exit(1); 
  }

  return 0;
}
