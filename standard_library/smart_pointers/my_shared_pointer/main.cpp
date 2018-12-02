#include <iostream>
#include "my_shared_ptr.h"

/*********************************************
 *           USAGE OF RAW POINTER            *
**********************************************/

class RawPointerUsage
{
  private:
    int* ptr {nullptr};

  public:
    RawPointerUsage(int* p);
    RawPointerUsage(const RawPointerUsage& rawPtr);
    RawPointerUsage(RawPointerUsage&& rawPtr);
    ~RawPointerUsage();
    void operator=(const RawPointerUsage& rawPtr);
    void operator=(RawPointerUsage&& rawPtr);
    
    friend void displayPtrInfo(const RawPointerUsage& rawPtr);
};

RawPointerUsage::RawPointerUsage(int* p)
: ptr {p}
{}

RawPointerUsage::RawPointerUsage(const RawPointerUsage& rawPtr)
: ptr { rawPtr.ptr }
{}

RawPointerUsage::RawPointerUsage(RawPointerUsage&& rawPtr)
: ptr { rawPtr.ptr }
{
  rawPtr.ptr = nullptr;
}

RawPointerUsage::~RawPointerUsage()
{
}

void RawPointerUsage::operator=(const RawPointerUsage& rawPtr)
{
  ptr = rawPtr.ptr;
}

void RawPointerUsage::operator=(RawPointerUsage&& rawPtr)
{
  ptr = rawPtr.ptr;
  rawPtr.ptr = nullptr;
}

void displayPtrInfo(const RawPointerUsage& rawPtr)
{
  using namespace std;
  cout << hex << "Address: " << rawPtr.ptr;
  if(rawPtr.ptr)
    cout << ", Value: " << *rawPtr.ptr;
  cout << endl;
}

/*********************************************
 *         USAGE OF SMART POINTER            *
**********************************************/

class SmartPointerUsage
{
  private:
    my::shared_ptr<int> ptr {nullptr};

  public:
    SmartPointerUsage(int value);
    SmartPointerUsage(int* p);
    SmartPointerUsage(const SmartPointerUsage& rawPtr);
    SmartPointerUsage(SmartPointerUsage&& rawPtr);
    ~SmartPointerUsage();
    void operator=(const SmartPointerUsage& rawPtr);
    void operator=(SmartPointerUsage&& rawPtr);
};

SmartPointerUsage::SmartPointerUsage(int value)
//: ptr {new int {123}}
: ptr {my::make_shared<int>(value)}
{}

SmartPointerUsage::SmartPointerUsage(int* p)
: ptr {p}
{}

SmartPointerUsage::SmartPointerUsage(const SmartPointerUsage& rawPtr)
: ptr { rawPtr.ptr }
{}

SmartPointerUsage::SmartPointerUsage(SmartPointerUsage&& rawPtr)
: ptr { std::move(rawPtr.ptr) }
{
}

SmartPointerUsage::~SmartPointerUsage()
{
}

void SmartPointerUsage::operator=(const SmartPointerUsage& rawPtr)
{
  ptr = rawPtr.ptr;
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
  int numbers[] {1, 2, 3};

  RawPointerUsage rawPtr1 {numbers};
  RawPointerUsage rawPtr2 {numbers + 1};
  RawPointerUsage rawPtr3 {numbers + 2};

  displayPtrInfo(rawPtr1);
  displayPtrInfo(rawPtr2);
  displayPtrInfo(rawPtr3);

  std::cout << "----------------------------------------" << std::endl;

  RawPointerUsage rawPtr4 {rawPtr1};
  RawPointerUsage rawPtr5 {std::move(rawPtr1)};
  rawPtr2 = rawPtr3;
  rawPtr3 = std::move(rawPtr4);
  
  displayPtrInfo(rawPtr1);
  displayPtrInfo(rawPtr2);
  displayPtrInfo(rawPtr3);
  displayPtrInfo(rawPtr4);
  displayPtrInfo(rawPtr5);

  SmartPointerUsage smartPtr1 {1};
  SmartPointerUsage smartPtr2 {2};
  SmartPointerUsage smartPtr3 {3};
  SmartPointerUsage smartPtr4 {smartPtr1};
  SmartPointerUsage smartPtr5 {std::move(smartPtr1)};
  smartPtr2 = smartPtr3;
  smartPtr3 = std::move(smartPtr4);

  std::cout << std::dec;

  my::shared_ptr<int, Deleter> p1 {new int {34543}, Deleter{}};
  std::cout << "p1 value: " << *p1 << std::endl;
  *p1 = 666;
  std::cout << "p1 value: " << *p1 << std::endl;
  int* rawPtr { p1.get() };
  std::cout << "p1 value: " << *rawPtr << std::endl;
  
  std::cout << "-----------------" << std::endl;

  my::shared_ptr<int> p2 {new int {121212}};
  std::cout << "p2 value: " << *p2 << std::endl;
  std::cout << "p2 value: " << *rawPtr << std::endl;

  std::cout << "-----------------" << std::endl;

  my::shared_ptr<int> p3 {new int {56789}};
  std::cout << "p3 value: " << *p3 << std::endl;
  p3.reset(new int {10});
  std::cout << "p3 value: " << *p3 << std::endl;

  std::cout << "-----------------" << std::endl;

  my::shared_ptr<int> p4 {new int {111}};
  my::shared_ptr<int> p5 {new int {222}};
  p4.swap(p5);
  std::cout << "p4 value: " << *p4 << std::endl;
  std::cout << "p5 value: " << *p5 << std::endl;

  std::cout << "-----------------" << std::endl;

  auto p6 {my::make_shared<int>(123)};
//  p6.reset();
  if(p6)
    std::cout << "before reset, p6 value: " << *p6 << std::endl;
  else
    std::cout << "after reset" << std::endl;

  std::cout << "-----------------" << std::endl;
 
  int* iptr { new int{ 444 } };
  my::shared_ptr<int> sharedPtr1 {iptr};
  std::cout << "sharedPtr1.use_count: " << sharedPtr1.use_count() << std::endl;
//  my::shared_ptr<int> sharedPtr2 {iptr}; // Don't do it! It' terated as another pointer
  my::shared_ptr<int> sharedPtr2 {sharedPtr1};
  std::cout << "sharedPtr2.use_count: " << sharedPtr2.use_count() << std::endl;
  my::shared_ptr<int> sharedPtr3 {sharedPtr1};
  std::cout << "sharedPtr3.use_count: " << sharedPtr3.use_count() << std::endl;
  my::shared_ptr<int> sharedPtr4 {sharedPtr2};
  std::cout << "sharedPtr4.use_count: " << sharedPtr4.use_count() << std::endl;
  my::shared_ptr<int> sharedPtr5 {std::move(sharedPtr1)};
  std::cout << "sharedPtr5.use_count: " << sharedPtr5.use_count() << std::endl;
  my::shared_ptr<int> sharedPtr6 {std::move(sharedPtr2)};
  std::cout << "sharedPtr6.use_count: " << sharedPtr6.use_count() << std::endl;
  my::shared_ptr<int> sharedPtr7 {sharedPtr3};
  std::cout << "sharedPtr7.use_count: " << sharedPtr7.use_count() << std::endl;

  std::cout << "-----------------" << std::endl;


  return 0;
}
