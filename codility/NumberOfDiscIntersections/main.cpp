#include <iostream>
#include <vector>


struct Disc
{
  int l,r;
};

int maxValue(std::vector<int>& vec)
{
  int max {0};
  for(auto e : vec)
  {
    if(e > max)
      max = e;
  }
  return max;
}

int solution(std::vector<int>& discs)
{
  const int N { static_cast<int>(discs.size())};
  int numOfIntersections {(N*N - N)/2};
 
  if(maxValue(discs) == 0)
    return 0;

  Disc* di { new Disc[N] };
  for(int i {}; i < N; i++)
  {
    di[i].l = i - discs[i];
    di[i].r = i + discs[i];
  }

  for(int i {}; i < N; i++)
  {
    for(int j {di[i].r + 1}; j < N; j++)
    {
      if(di[i].r < di[j].l)
        numOfIntersections--;
    }
  }

  delete [] di;

  return (numOfIntersections <= 10000000) ? numOfIntersections : -1;
}

int main()
{
  constexpr int N {6};
//  int discs[N]{};
  std::vector<int> discs {};
  discs.resize(N);

  discs[0] = 1;
  discs[1] = 5;
  discs[2] = 2;
  discs[3] = 1;
  discs[4] = 4;
  discs[5] = 0;

  std::cout << solution(discs) << std::endl;

  return 0;
}
