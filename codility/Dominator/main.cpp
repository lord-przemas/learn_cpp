#include <iostream>
#include <random>
#include <vector>
 

struct SampleEntry
{
  int value;
  unsigned int index;
  bool isCounted {false};
  unsigned int counter {0};
};


void randValues(SampleEntry* samples, int sampleSize, const std::vector<int>& vec)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::uniform_int_distribution<unsigned int> dis(0, vec.size());

    for(int i {}; i < sampleSize; i++)
    {
      samples[i].index = dis(rd);
      samples[i].value = vec[samples[i].index];
    }
}

int solution(std::vector<int>& vec)
{
  if(vec.size() == 0)
    return -1;
  else if(vec.size() <= 2)
    return 0;

  constexpr int SAMPLE_SIZE {200};
  SampleEntry* samples = new SampleEntry[SAMPLE_SIZE];
  randValues(samples, SAMPLE_SIZE, vec);

  for(int i {}; i < SAMPLE_SIZE; i++)
  {
    for(int j {i}; j < SAMPLE_SIZE; j++)
    {
      if(samples[i].value == samples[j].value && samples[j].isCounted == false)
      {
        samples[i].counter++;
        samples[j].isCounted = true;
      }
    }
  }

  constexpr unsigned int thresholdFinish { 120 };
  constexpr unsigned int thresholdVerify { 80 };
  for(int i {}; i < SAMPLE_SIZE; i++)
  {
    if(samples[i].counter > thresholdFinish)
    {
      return samples[i].index; 
    }
    else if(samples[i].counter > thresholdVerify)
    {
      unsigned int realCounter {0};
      for(auto e : vec)
      {
        if(e == samples[i].value)
          realCounter++;
      }
      if(realCounter > vec.size() / 2)
        return samples[i].index;
    }
  }

  delete [] samples;

  return -1;
}

int main()
{
  std::vector<int> vec {};
  vec.resize(1);

  std::cout << "Result: " << solution(vec) << std::endl;

  return 0;
}
