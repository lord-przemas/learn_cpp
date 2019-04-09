#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <thread>
#include <future>


int main()
{

  int seed;
  do {
    std::cout << "seed value : ";
    std::cin >> seed;
    if(std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
      std::cout << "Type error: The seed value  must be a number!" << std::endl;
    }
    else break;

  } while (true);

  const std::vector<std::string> words { "Ala", "ma", "bobra", "Hello", "World", "cpp", "lesson" };
  const int words_size { static_cast<int>(words.size()) };
  constexpr int COUNT {1000};

  std::random_device generator;
  std::mt19937 mt {seed};

  std::cout << " --- Generate words_uniform.txt" << std::endl;
  {
    std::ofstream file {"words_uniform.txt"};
    std::uniform_int_distribution<int> dist {0, static_cast<int>(words.size()) - 1};

    for(int i {}; i < COUNT; i++) {
      auto index = dist(mt);
      file << words.at(index) << '\n';
    }
  }

  std::cout << " --- Generate words_normal.txt" << std::endl;
  {
    std::ofstream file {"words_normal.txt"};
    std::normal_distribution dist {static_cast<double>(words.size()-1) / 2.0, 1.3};

    for(int i {}; i < COUNT;) {
      auto index = static_cast<int>(std::round(dist(mt)));
      if(index >= 0 && index < words_size) {
        file << words.at(index) << '\n';
        i++;
      }
    }
  }

  std::cout << " --- Generate words_uniform_th_4.txt" << std::endl;
  {
    std::ofstream file {"words_uniform_th_4.txt"};
    std::uniform_int_distribution<int> dist {0, static_cast<int>(words.size()) - 1};

    std::mutex m{};
    auto task = [&](int th_num, int th_count){
      for(int i {th_num}; i < COUNT; i += th_count) {
        std::lock_guard<std::mutex> lguard {m};
        auto index = dist(mt);
        file << words.at(index) << '\n';
      }
      std::cout << "thread " << th_num << " is running..." << std::endl;
    };

    auto f1 = std::async(std::launch::async, task, 0, 4);
    auto f2 = std::async(std::launch::async, task, 1, 4);
    auto f3 = std::async(std::launch::async, task, 2, 4);
    auto f4 = std::async(std::launch::async, task, 3, 4);

//    std::thread th1 {task, 0, 4};
//    std::thread th2 {task, 1, 4};
//    std::thread th3 {task, 2, 4};
//    std::thread th4 {task, 3, 4};
//
//    th1.join();
//    th2.join();
//    th3.join();
//    th4.join();
  }

  std::cout << " --- Generate words_normal_th_4.txt" << std::endl;
  {
    std::ofstream file {"words_normal_th_4.txt"};
    std::normal_distribution dist {static_cast<double>(words.size()-1) / 2.0, 1.3};

    std::mutex m{};
    auto task = [&](int th_num, int th_count){
      for(int i {th_num}; i < COUNT;) {
        auto index = static_cast<int>(std::round(dist(mt)));
        if(index >= 0 && index < words_size) {
        std::lock_guard<std::mutex> lguard {m};
          file << words.at(index) << '\n';
          i += th_count;
        }
      }
      std::cout << "thread " << th_num << " is running..." << std::endl;
    };

    auto f1 = std::async(std::launch::async, task, 0, 4);
    auto f2 = std::async(std::launch::async, task, 1, 4);
    auto f3 = std::async(std::launch::async, task, 2, 4);
    auto f4 = std::async(std::launch::async, task, 3, 4);

//    std::thread th1 {task, 0, 4};
//    std::thread th2 {task, 1, 4};
//    std::thread th3 {task, 2, 4};
//    std::thread th4 {task, 3, 4};
//
//    th1.join();
//    th2.join();
//    th3.join();
//    th4.join();
  }


  //  std::map<int, int> hist{};
  //
  //  for(int i {}; i < COUNT; i++)
  //    ++hist[std::round(dist(mt))];
  //
  //  for(auto e : hist)
  //    std::cout << e.first << " : " << e.second << std::endl;



  return 0;
}
