#include <iostream>
#include <vector>

#include <numeric>

struct ArrayInfo
{
  int* first;
  int* last;
  int sumOfElements;
};


int solution(int K, int M, std::vector<int>& data)
{
  const int N = data.size();

  ArrayInfo* info = new ArrayInfo[K];
  info[0].first = &data[0];
  info[0].last = &data[N-1];
  info[0].sumOfElements = std::accumulate(data.begin(), data.end(), 0);

  for(int i {1}; i < K; i++)
  {
    info[i].first = &data[N];
    info[i].last = &data[N-1];
    info[i].sumOfElements = 0;
  }

  bool finish {false};
  while(!finish)
  {
    finish = true;
    for(int i {}; i < K - 1; i++)
    {
      int j {i+1};
      int currentSum1 { info[i].sumOfElements };
      int currentSum2 { info[j].sumOfElements };
      int updatedSum1 { info[i].sumOfElements - *(info[i].last) };
      int updatedSum2 { info[j].sumOfElements + *(info[i].last) };
      if((currentSum1 - currentSum2) >= (updatedSum2 - updatedSum1))
      {
        info[i].sumOfElements = updatedSum1;
        info[j].sumOfElements = updatedSum2;
        info[i].last--;
        info[j].first--;
        finish = false;
      }
    }
  }

  int maxSum {0};
  for(int i {}; i < K; i++)
    if(info[i].sumOfElements > maxSum)
      maxSum = info[i].sumOfElements;

  delete [] info;

  return maxSum;
}

int main()
{

  constexpr int N {1000};
//  std::vector<int> data {3, 4, 5, 6, 7, 8};
  std::vector<int> data {5, 2, 3, 4, 6};
//  data.resize(N);

//  data[500] = 99;

//  data[0] = 2;
//  data[1] = 1;
//  data[2] = 11;
//  data[3] = 12;
//  data[4] = 2;
//  data[5] = 2;
//  data[6] = 12;

  std::cout << solution(3, 5, data) << std::endl;;

  return 0;
}
