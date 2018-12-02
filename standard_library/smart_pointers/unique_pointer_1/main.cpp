#include <iostream>
#include <memory>

/*********************************************
 *           USAGE OF RAW POINTER            *
**********************************************/

class RawPointerUsage
{
  private:
    int* ptr {nullptr};

  public:
    RawPointerUsage(int x);
    RawPointerUsage(const RawPointerUsage& rawPtr);
    RawPointerUsage(RawPointerUsage&& rawPtr);
    ~RawPointerUsage();
    void operator=(const RawPointerUsage& rawPtr);
    void operator=(RawPointerUsage&& rawPtr);
};

RawPointerUsage::RawPointerUsage(int x)
: ptr {new int {x}}
{}

RawPointerUsage::RawPointerUsage(const RawPointerUsage& rawPtr)
: ptr {new int {*rawPtr.ptr}}
{}

RawPointerUsage::RawPointerUsage(RawPointerUsage&& rawPtr)
: ptr {rawPtr.ptr}
{
  rawPtr.ptr = nullptr;
}

RawPointerUsage::~RawPointerUsage()
{
  delete ptr;
}

void RawPointerUsage::operator=(const RawPointerUsage& rawPtr)
{
  *ptr = *rawPtr.ptr;
}

void RawPointerUsage::operator=(RawPointerUsage&& rawPtr)
{
  delete ptr;
  ptr = rawPtr.ptr;
  rawPtr.ptr = nullptr;
}

/*********************************************
 *         USAGE OF SMART POINTER            *
**********************************************/

class SmartPointerUsage
{
  private:
    std::unique_ptr<int> ptr {nullptr};

  public:
    SmartPointerUsage(int x);
    SmartPointerUsage(const SmartPointerUsage& rawPtr);
    SmartPointerUsage(SmartPointerUsage&& rawPtr);
    ~SmartPointerUsage();
    void operator=(const SmartPointerUsage& rawPtr);
    void operator=(SmartPointerUsage&& rawPtr);
};

SmartPointerUsage::SmartPointerUsage(int x)
: ptr {std::make_unique<int>(x)}
{}

SmartPointerUsage::SmartPointerUsage(const SmartPointerUsage& rawPtr)
: ptr {std::make_unique<int>(*rawPtr.ptr)}
{}

SmartPointerUsage::SmartPointerUsage(SmartPointerUsage&& rawPtr)
: ptr {std::move(rawPtr.ptr)}
{
}

SmartPointerUsage::~SmartPointerUsage()
{
}

void SmartPointerUsage::operator=(const SmartPointerUsage& rawPtr)
{
  *ptr = *rawPtr.ptr;
}

void SmartPointerUsage::operator=(SmartPointerUsage&& rawPtr)
{
  ptr = std::move(rawPtr.ptr);
}

class Deleter
{
  public:
  void operator()(int* p) const
  {
    if(p)
      std::cout << "Deleting pointer to int... (value: "<< *p <<")" << std::endl;

    delete p;
  }
};

int main()
{
  
  RawPointerUsage rawPtr1 {1};
  RawPointerUsage rawPtr2 {2};
  RawPointerUsage rawPtr3 {rawPtr1};
  RawPointerUsage rawPtr4 {std::move(rawPtr1)};
  rawPtr2 = rawPtr3;
  rawPtr3 = std::move(rawPtr4);


  SmartPointerUsage smartPtr1 {1};
  SmartPointerUsage smartPtr2 {2};
  SmartPointerUsage smartPtr3 {smartPtr1};
  SmartPointerUsage smartPtr4 {std::move(smartPtr1)};
  smartPtr2 = smartPtr3;
  smartPtr3 = std::move(smartPtr4);

  std::unique_ptr<int[]> tbl1 {new int[3] {1,2,3}};
  tbl1[1] = 123;

  std::unique_ptr<int[]> tbl2 {std::make_unique<int[]>(3)};
  tbl2[1] = 123;

  std::cout << "-----------------" << std::endl;

  std::unique_ptr<int, Deleter> p1 {new int {34543}};
  std::cout << "p1 value: " << *p1 << std::endl;
  *p1 = 666;
  std::cout << "p1 value: " << *p1 << std::endl;
  int* rawPtr { p1.get() };
  std::cout << "p1 value: " << *rawPtr << std::endl;
  
  std::cout << "-----------------" << std::endl;

  std::unique_ptr<int, Deleter> p2 {new int {121212}};
  std::cout << "p2 value: " << *p2 << std::endl;
  rawPtr = p2.release();
  std::cout << "p2 value: " << *rawPtr << std::endl;
//  delete rawPtr;
  auto deleter {p2.get_deleter()};
  deleter(rawPtr);

  std::cout << "-----------------" << std::endl;

  std::unique_ptr<int, Deleter> p3 {new int {56789}};
  std::cout << "p3 value: " << *p3 << std::endl;
  p3.reset(new int {10});
  std::cout << "p3 value: " << *p3 << std::endl;

  std::cout << "-----------------" << std::endl;

  std::unique_ptr<int, Deleter> p4 {new int {111}};
  std::unique_ptr<int, Deleter> p5 {new int {222}};
  p4.swap(p5);
  std::cout << "p4 value: " << *p4 << std::endl;
  std::cout << "p5 value: " << *p5 << std::endl;

  std::cout << "-----------------" << std::endl;

  auto p6 {std::make_unique<int>(123)};
//  p6.reset();
  if(p6)
    std::cout << "before reset, p6 value: " << *p6 << std::endl;
  else
    std::cout << "after reset" << std::endl;

  std::cout << "-----------------" << std::endl;


  return 0;
}
