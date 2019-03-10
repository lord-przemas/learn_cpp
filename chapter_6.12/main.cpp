#include <iostream>
#include <memory>

template <typename T>
class Table final
{
  private:
    std::unique_ptr<T[]> tbl { nullptr };
    const size_t TBL_SIZE {};

  public:
    Table() = delete;
    Table(const Table<T>&);
    Table(Table<T>&&);
    Table(std::initializer_list<T> li);
    ~Table() = default;

    T& operator[](int index) const { return tbl[index]; }
    T* begin() const { return tbl.get(); }
    T* end() const { return tbl.get() + TBL_SIZE; }
    const T* cbegin() const { return tbl.get(); }
    const T* cend() const { return tbl.get() + TBL_SIZE; }
    size_t size() const { return TBL_SIZE; };

};

template <typename T>
Table<T>::Table(std::initializer_list<T> li)
  : tbl { new T[ li.size() ] },
    TBL_SIZE { li.size() }
{
  std::cout << "Custom ctor" << std::endl;
  int index {};
  for (const auto& element : li)
  {
    tbl[index++] = element;
  }
}

template <typename T>
Table<T>::Table(const Table<T>& table)
  : tbl { new T[ table.size() ] },
    TBL_SIZE { table.size() }
{
  std::cout << "Copy ctor" << std::endl;
  int index {};
  for (const auto& element : table)
  {
    tbl[index++] = element;
  }
}

template <typename T>
Table<T>::Table(Table<T>&& table)
  : tbl { std::move(table.tbl) },
    TBL_SIZE { table.size() }
{
  std::cout << "Move ctor" << std::endl;
}

template <typename T, typename... Args>
Table<T> createTable(T&& arg0, Args&&... args)
{
  return Table<T> {std::forward<T>(arg0), std::forward<T>(args)...};
}


int main()
{

  Table<float> tbl {1.34, 2.5, 3.23, 4.23, 5.0};

  tbl[2] = 4353;

  for(auto& element : tbl)
  {
    std::cout << element << std::endl;
  }

  std::cout << "----------------" << std::endl;

  const Table<float> copyTable {tbl};

  for(auto element : copyTable)
  {
    std::cout << element << std::endl;
  }

  std::cout << "----------------" << std::endl;

  const Table<float> moveTable { createTable(1.234f, 2323.25f, 435.234f) };

  moveTable[4] = 7.77;

  for(auto element : moveTable)
  {
    std::cout << element << std::endl;
  }


  return 0;
}
