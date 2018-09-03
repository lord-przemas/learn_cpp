#include <iostream>

void passArray1(int tbl[3])
{
}

void passArray2(int* tbl)
{
}

void passArray3(int tbl[])
{
}

void passArray4(const int tbl[])
{
}

void wrongArraySize(int tbl[])
{
  std::cout << sizeof(tbl) << std::endl;
}

void correctArraySize(int (&tbl)[6])
{
  std::cout << sizeof(tbl) << std::endl;
}

template <typename T>
class Array final
{
  private:
    T* tbl { nullptr };
    const size_t size {};

  public:
    Array(std::initializer_list<T> l);
    ~Array();
    T& operator[](int i) { return tbl[i]; }
    size_t length() const { return size; }
    T* begin() const { return tbl; }
    T* end() const { return tbl + size; }
    
    Array() = delete;
    Array(const Array&) = delete;
    void operator=(const Array&) = delete;
};

template <typename T>
Array<T>::Array(std::initializer_list<T> l)
  : tbl {new T [l.size()]}, size {l.size()}
{
  size_t i {};
  for(auto item : l)
    tbl[i++] = item;
}

template <typename T>
Array<T>::~Array()
{
  delete [] tbl;
}


int main()
{
  int tbl[] {1,2,3,4,5,6};

  passArray1(tbl);
  passArray2(tbl);
  passArray3(tbl);
  passArray4(tbl);

  std::cout << sizeof(tbl) << std::endl;
  wrongArraySize(tbl);
  correctArraySize(tbl);


  Array tbl1 = {2.4, 5.232, 65.33, 64.23, 875.345};
  for(int i {}; i <= tbl1.length(); ++i)
  {
    std::cout << tbl1[i] << std::endl;
    tbl1[i] = 234.235;
  }

  Array<int> tbl2 = {1,3,4,67,3};
  for(auto item : tbl2)
    std::cout << item << std::endl;

  Array textTbl {"chuj", "dupa", "Siema Heniu!"};
  for(auto item : textTbl)
    std::cout << item << std::endl;


  return 0;
}
