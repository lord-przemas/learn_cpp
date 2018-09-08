#include <iostream>

template <typename T>
class Table final
{
  private:
    T* tbl { nullptr };
    const size_t TBL_SIZE {};

  public:
    Table() = delete;
    Table(const Table&) = delete;
    Table(std::initializer_list<T> li);
    ~Table();

    T& operator[](int index) const { return tbl[index]; }
    T* begin() const { return tbl; }
    T* end() const { return tbl + TBL_SIZE; }
    const T* cbegin() const { return tbl; }
    const T* cend() const { return tbl + TBL_SIZE; }
};

template <typename T>
Table<T>::Table(std::initializer_list<T> li)
  : tbl { new T[ li.size() ] },
    TBL_SIZE { li.size() }
{
  int index {};
  for (const auto& element : li)
  {
    tbl[index++] = element;
  }
}

template <typename T>
Table<T>::~Table()
{
  delete [] tbl;
}

int main()
{

  Table tbl {1.34, 2.5, 3.23, 4.23, 5.0};

  tbl[2] = 4353;

  for(auto& element : tbl)
  {
    std::cout << element << std::endl;
  }

  return 0;
}
