#include <cstdio>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>


struct Text
{
    static constexpr int LENGTH {20};
    char text[LENGTH] {};
    std::mutex m;
};

int main()
{

  printf ("****** SECTION: Usage of the std::thread ********\n");
  {
    auto foo = [](int threadNum, int delay){
      printf ("Thread %d is running...\n", threadNum);
      std::this_thread::sleep_for(std::chrono::seconds(delay));
    };
  
    printf ("%d concurrent threads are supported.\n", std::thread::hardware_concurrency());
    printf ("----------------------------\n");
  
    {
      std::thread th1 { foo, 1, 1 };
      std::thread th2 { foo, 2, 2 };
      std::thread th3 { foo, 3, 3 };
      th1.join();
      printf ("join 1\n");
      th2.join();
      printf ("join 2\n");
      th3.join();
      printf ("join 3\n");
    
      foo(999, 5);
    }
  
    printf ("----------------------------\n");
  
    {
      std::thread th1 { foo, 1, 1 };
      std::thread th2 { foo, 2, 2 };
      std::thread th3 { foo, 3, 3 };
      th1.detach();
      printf ("detach 1\n");
      th2.detach();
      printf ("detach 2\n");
      th3.detach();
      printf ("detach 3\n");
    
      foo(999, 5);
    }
  
    printf ("----------------------------\n");
  }

  printf ("****** SECTION: Usage of the std::mutex ********\n");
  {
    constexpr int TAB_SIZE {16};
    int shared[TAB_SIZE] {};

    std::mutex mmutex {};
    auto foo2 = [&shared, &mmutex] (int num){
      mmutex.lock();
      for(auto& t : shared)
      {
        t = num;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
      mmutex.unlock();
    };
    
    auto foo3 = [&shared, &mmutex] (int num){
//      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      if(mmutex.try_lock())
      {
        for(auto& t : shared)
        {
          t = num;
        }
        mmutex.unlock();
      }
      else
        printf("Lock failed!\n");
    };

    constexpr int NUM_OF_THREADS {10};
    std::thread th[NUM_OF_THREADS] {};
    std::thread th1{foo3, 123};
    for(int i {}; i < NUM_OF_THREADS; i++)
    {
      th[i] = std::thread { foo2, i};
    }

    for(auto& t : th)
      t.join();
    th1.join();

    for(auto t : shared)
      printf("%d\n", t);
  }

  printf ("****** SECTION: Usage of the std::lock_guard ********\n");
  {
    constexpr int TAB_SIZE {16};
    int shared[TAB_SIZE] {};

    std::mutex mmutex {};
    auto foo = [&shared, &mmutex] (int num){
      std::lock_guard<std::mutex> lock {mmutex, std::adopt_lock};
      for(auto& t : shared)
      {
        t = num;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    };

    constexpr int NUM_OF_THREADS {10};
    std::thread th[NUM_OF_THREADS] {};
    for(int i {}; i < NUM_OF_THREADS; i++)
    {
      th[i] = std::thread { foo, i};
    }

    for(auto& t : th)
      t.join();

    for(auto t : shared)
      printf("%d\n", t);
  }

  printf ("****** SECTION: Usage of the std::scoped_lock ********\n");
  {
    const char charArray1 [Text::LENGTH] {"abcdefghijklmnoprst"};
    const char charArray2 [Text::LENGTH] {"0123456789012345678"};

    auto changeText = [&charArray1, &charArray2](Text& t1, Text& t2)
    {
      std::scoped_lock slock {t1.m, t2.m};
      for(int i {}; i < Text::LENGTH; i++)
      {
        t1.text[i] = charArray1[i];
        t2.text[i] = charArray2[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
    };


    Text texts[4] {};
    std::vector<std::thread> threads {};
    threads.emplace_back(changeText,  std::ref(texts[0]), std::ref(texts[1]));
    threads.emplace_back(changeText,  std::ref(texts[1]), std::ref(texts[2]));
    threads.emplace_back(changeText,  std::ref(texts[2]), std::ref(texts[3]));
    threads.emplace_back(changeText,  std::ref(texts[3]), std::ref(texts[0]));
    threads.emplace_back(changeText,  std::ref(texts[0]), std::ref(texts[1]));
    threads.emplace_back(changeText,  std::ref(texts[1]), std::ref(texts[2]));
    threads.emplace_back(changeText,  std::ref(texts[2]), std::ref(texts[3]));
    threads.emplace_back(changeText,  std::ref(texts[3]), std::ref(texts[0]));

    for(auto& th : threads)
      th.join();

    for(const auto& t : texts)
      printf("%s\n", t.text);
  }

  printf ("\n****** SECTION: Usage of the std::future with std::promise ********\n");
  {
    using Type = int;
    std::promise<Type> p {};
    std::future<Type> f { p.get_future() };
    std::thread th { [&p] (Type value) {
      printf("std::thread with std::promise is running...\n");
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("Set value to %d.\n", value);
      p.set_value(value);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::thread has finished.\n");
    }, 444};

    f.wait();
    Type value { f.get() };
    printf("Value returned by thread is %d\n", value);

    th.join();
    printf("Main thread has finished.\n");
  }

  printf ("\n****** SECTION: Usage of the std::future with std::packaged_task ********\n");
  {
    using Type = int;
    std::packaged_task<Type(Type,Type)> task { [] (Type a, Type b) {
      printf("std::thread with std::packaged_task is running...\n");
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::thread has finished.\n");
      return a + b;
    }};
    
    std::future<Type> f { task.get_future() };
    std::thread th { std::move(task), 1, 2 };
    th.join();

    Type value { f.get() };
    printf("Value returned by thread is %d\n", value);
    printf("Main thread has finished.\n");
  }

  printf ("\n****** SECTION: Usage of the std::future with std::async ********\n");
  {
    using Type = int;
    std::future<Type> f1 = std::async(std::launch::deferred, [] (Type a, Type b) {
      printf("std::async %d is running...\n", a);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::async has finished.\n");
      return a + b;
    }, 1, 2);

    std::future<Type> f2 = std::async(std::launch::deferred, [] (Type a, Type b) {
      printf("std::async %d is running...\n", a);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::async has finished.\n");
      return a + b;
    }, 2, 7);

    std::future<Type> f3 = std::async(std::launch::deferred, [] (Type a, Type b) {
      printf("std::async %d is running...\n", a);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::async has finished.\n");
      return a + b;
    }, 3, 2);

    std::future<Type> f4 = std::async(std::launch::deferred, [] (Type a, Type b) {
      printf("std::async %d is running...\n", a);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      printf("std::async has finished.\n");
      return a + b;
    }, 4, 7);

    Type value1 { f3.get() };
    Type value2 { f2.get() };
    Type value3 { f1.get() };
    Type value4 { f4.get() };
    printf("Value returned by thread is %d\n", value1);
    printf("Value returned by thread is %d\n", value2);
    printf("Value returned by thread is %d\n", value3);
    printf("Value returned by thread is %d\n", value4);
    printf("Main thread has finished.\n");
  }

  return 0;
}
