#include <iostream>
#include <thread>
#include <chrono>
#include <ratio>

int main()
{

  // *** Duration and ratio
  std::chrono::seconds sec { 5 };
  std::chrono::duration<int, std::ratio<1, 1>> unit { sec };
  std::cout << "unit: " << unit.count() << std::endl;

  std::chrono::duration<int, std::ratio<1, 1000>> milisec { std::chrono::seconds{ 3 } };
  std::cout << "mili: " << milisec.count() << std::endl;

  milisec = std::chrono::milliseconds{ 3 };
  std::cout << "mili: " << milisec.count() << std::endl;

  auto h = std::chrono::hours { 3 };
  std::chrono::duration<int, std::ratio<60, 1>> mins { h };
  std::cout << "minutes: " << mins.count() << std::endl;
  std::chrono::duration<int, std::ratio<60 * 60, 1>> hs { h };
  std::cout << "hours: " << hs.count() << std::endl;


  // *** Clocks
  {
    std::chrono::time_point<std::chrono::system_clock> start { std::chrono::system_clock::now() };
    std::this_thread::sleep_for(std::chrono::milliseconds { 1234 });
    std::chrono::time_point<std::chrono::system_clock> end { std::chrono::system_clock::now() };
    std::chrono::duration<double> diff_time { end - start };

    std::cout << "diff_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(diff_time).count() << std::endl;
    std::cout << "diff_time: " << diff_time.count() << std::endl;

    std::time_t start_time { std::chrono::system_clock::to_time_t(start) };
    std::cout << "time: " << std::ctime(&start_time) << std::endl;
  }


  {
    std::chrono::time_point<std::chrono::steady_clock> start { std::chrono::steady_clock::now() };
    std::this_thread::sleep_for(std::chrono::milliseconds { 1234 });
    std::chrono::time_point<std::chrono::steady_clock> end { std::chrono::steady_clock::now() };
    std::chrono::duration<double> diff_time { end - start };

    std::cout << "diff_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(diff_time).count() << std::endl;
    std::cout << "diff_time: " << diff_time.count() << std::endl;
  }


  return 0;
}
