#include <thread>
#include <future>
#include <mutex>
#include <cstdio>

#include <unistd.h>
#include <sys/wait.h>


std::mutex m {};

void tryDeadlock()
{
  while(true)
  {
  m.lock();
  printf("tryDeadlock begin!\n");
  printf("tryDeadlock is running...\n");
  std::this_thread::sleep_for(std::chrono::seconds(3));
  printf("tryDeadlock end!\n");
  m.unlock();
  }
}

//int main() {
//
//  std::thread th { tryDeadlock };
//
//  std::this_thread::sleep_for(std::chrono::milliseconds(20));
//  auto asyncJob = std::async(std::launch::async, []{
//      tryDeadlock();
//      });
//
//  for(int j = 0; true; ++j) 
//  {
//    if (asyncJob.wait_for(std::chrono::milliseconds(300)) == std::future_status::ready)
//    {
//      printf("Bye child\n");
//      break;
//    }
//    else 
//    {
//      printf("Waiting for child process...\n");
//    }
//  }
//
//
//  th.join();
//
//  return 0;
//}

int main() {

  std::thread th { tryDeadlock };

  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  const auto forkResult = fork();
  if(forkResult == 0) // Child process
  {
    tryDeadlock();
  }
  else // Parent process
  {
    int status {};
    for(int j = 0; true; ++j) 
    {
      const auto waitResult = waitpid(forkResult, &status, WNOHANG);
      if(-1 == waitResult) 
      {
        printf("waitpid() failed!\n");
      } 
      else if (waitResult == 0)
      {
        printf("Waiting for child process...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
      }
      else 
      {
        printf("Bye child\n");
        break;
      }
    }
  }


  th.join();

  return 0;
}

