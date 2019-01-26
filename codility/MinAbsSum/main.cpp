#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int solution(std::vector<int>& vec)
{
  if(vec.size() == 0)
    return 0;

  std::sort(vec.begin(), vec.end(), [](int a, int b)
      {
        return abs(a) > abs(b);
      });

  int sum {*vec.begin()};

  for(auto it {vec.begin() + 1}; it < vec.end(); it++)
  {
    int element {*it};
    if(abs(sum + element) > abs(sum - element))
      sum -= element;
    else
      sum += element;
  }

  return abs(sum);
}


int main()
{

  std::vector<int> vec {3, 3, 3, 4, 5};

  std::cout << solution(vec) << std::endl;

  return 0;
}
