#include <iostream>
#include <utility>
#include <memory>


class HeavyObject
{
  public:
    HeavyObject() = default;
    HeavyObject(const HeavyObject& hobj)
    {
      std::cout << "HeavyObject(const HeavyObject& hobj)" << std::endl;
    }

    HeavyObject(HeavyObject&& hobj)
    {
      std::cout << "HeavyObject(HeavyObject&& hobj)" << std::endl;
    }
};

template <typename T>
void createHeavyObject(T&& obj)
{
  HeavyObject moveObj {std::move(obj)};
  HeavyObject forwardObj {std::forward<T>(obj)};
}

int main()
{

  HeavyObject obj {};
  createHeavyObject(obj);
  std::cout << "-------------------------" << std::endl;
  createHeavyObject(HeavyObject{});
  std::cout << "-------------------------" << std::endl;
  createHeavyObject(std::move(obj));


  return 0;
}


//class Entry
//{
//  public:
//    Entry(){
//      std::cout << "Entry()" << std::endl;
//    }
//    Entry(const Entry&){
//      std::cout << "Entry(const Entry&)" << std::endl;
//    }
//    Entry(Entry&&){
//      std::cout << "Entry(Entry&&)" << std::endl;
//    }
//    void operator=(const Entry&){
//      std::cout << "operator=(const Entry&)" << std::endl;
//    }
//    void operator=(Entry&&){
//      std::cout << "operator=(Entry&&)" << std::endl;
//    }
//};
//
//template <typename T, typename... Args>
//class TableWrapper
//{
//  private:
//    std::unique_ptr<T[]> tbl {nullptr};
//
//  public:
//    TableWrapper(const T& arg0, const Args&... args)
//      : tbl { new T[1 + sizeof...(Args)]{arg0, args...} }
//    {
//      std::cout << "TableWrapper(const T& arg0, const Args&... args)" << std::endl;
//      std::cout << "Size: " << (1 + sizeof...(Args)) << std::endl;
//    }
//
//    TableWrapper(T&& arg0, Args&&... args)
//      : tbl { new T[1 + sizeof...(Args)]{std::forward<T>(arg0), std::forward<T>(args)...} }
//    {
//      std::cout << "TableWrapper(T&& arg0, Args&&... args)" << std::endl;
//      std::cout << "Size: " << (1 + sizeof...(Args)) << std::endl;
//    }
//};
//
//int main()
//{
//
////  TableWrapper tbl {1,2,3,4,5};
//  TableWrapper tbl1 {Entry{}, Entry{}, Entry{}};
//
//  std::cout << "----------------------" << std::endl;
//
//  Entry e1 {};
//  Entry e2 {};
//  Entry e3 {};
//  TableWrapper tbl2 {e1, e2, e3};
//
//  return 0;
//}

