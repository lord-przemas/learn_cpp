#include <iostream>
#include <random>
#include <map>


int mrandom()
{
  static constexpr int a {4};
  static constexpr int c {1};
  static constexpr int m {9};
  static int value { 0 };
  value = (a * value + c) % m;
  return value;
}

int main()
{
  auto run = [](auto& randomGenerator, int count)
  {
    for(int i {}; i < count; i++)
    {
      std::cout << randomGenerator() << ", ";
    }
    std::cout << std::endl;
  };


  std::cout << "------ Random number engines ------" << std::endl;

  run(mrandom, 10);

  std::linear_congruential_engine<uint32_t, 4, 1, 9> lincEngine {0};
  run(lincEngine, 10);


  std::mt19937 mtEngine{123};
  run(mtEngine, 10);

  std::subtract_with_carry_engine<std::uint_fast32_t, 32, 103, 250> swceEngine{};
  run(swceEngine, 10);

  std::cout << std::endl;


  std::cout << "------ Random number engine adaptors ------" << std::endl;

  using LinearEngine = std::linear_congruential_engine<uint32_t, 11, 2, 1000>;
  std::discard_block_engine<LinearEngine, 5, 3> discardAdaptor {};
  LinearEngine linearEngine {};
  for(int i {}; i < 20; i++)
  {
    auto linValue = linearEngine();
    auto disValue = discardAdaptor();

    while(disValue != linValue)
    {
      std::cout << " -  : " << linValue << "\n";
      linValue = linearEngine();
    }
    std::cout << disValue << " : " << linValue << std::endl;

  }
  std::cout << std::endl;

  using LinearEngine2 = std::linear_congruential_engine<uint32_t, 9, 7, 0x10000>;
  std::independent_bits_engine<LinearEngine2, 14, uint16_t> bitsAdaptor {};
  LinearEngine2 lincEngine2 {};
  run(bitsAdaptor, 10);
  run(lincEngine2, 10);

  std::cout << std::endl;

  using LinearEngine3 = std::linear_congruential_engine<uint32_t, 2, 7, 100>;
  std::shuffle_order_engine<LinearEngine3, 5> shuffleAdaptor {};
  LinearEngine3 lincEngine3 {};
  run(shuffleAdaptor, 15);
  run(lincEngine3, 15);

  std::cout << std::endl;


  std::cout << "------ Non-deterministic random numbers ------" << std::endl;

  std::random_device rd {};
  run(rd, 10);
  run(rd, 10);

  std::cout << std::endl;

  // ***************************************************************************
  std::cout << "********* Random number distributions *********" << std::endl;

  auto runDistribution = [](auto& distribution, auto& randomGenerator, int count)
  {
    for(int i {}; i < count; i++)
    {
      std::cout << distribution(randomGenerator) << ", ";
    }
    std::cout << std::endl;
  };

  std::random_device randomDevice {};
  std::linear_congruential_engine<uint32_t, 2, 1, 10000> randomLinearEngine {0};
  std::mt19937 randomMTEngine{3};


  std::cout << "------ Uniform distributions ------" << std::endl;

  std::uniform_int_distribution uniform {1, 100};
  runDistribution(uniform, randomDevice, 10);
  runDistribution(uniform, randomLinearEngine, 10);
  runDistribution(uniform, randomMTEngine, 10);

  std::cout << std::endl;


  std::cout << "------ Bernoulli distributions ------" << std::endl;

  std::bernoulli_distribution bernoulli {};
  runDistribution(bernoulli, randomDevice, 10);
  runDistribution(bernoulli, randomLinearEngine, 10);
  runDistribution(bernoulli, randomMTEngine, 10);

  auto bernoulliHistogram = [](auto& distribution, auto& randomGenerator, int count)
  {
    std::map<bool, int> hist{};
    for(int i {}; i < count; i++)
      ++hist[distribution(randomGenerator)];

    std::cout << "true: " << hist.at(true) << std::endl;
    std::cout << "false: " << hist.at(false) << std::endl;
    std::cout << std::endl;
  };

  bernoulliHistogram(bernoulli, randomDevice, 1000);
  bernoulliHistogram(bernoulli, randomLinearEngine, 1000);
  bernoulliHistogram(bernoulli, randomMTEngine, 1000);

  std::cout << std::endl;


  std::cout << "------ Normal distributions ------" << std::endl;

  std::normal_distribution normal {100.0, 2.5};
  runDistribution(normal, randomDevice, 10);

  std::cout << std::endl;

  std::map<int, int> hist2{};
  for(int i {}; i < 1000; i++)
    ++hist2[std::round(normal(randomDevice))];

  for(auto e : hist2)
    std::cout << e.first << ": " << e.second << std::endl;


  return 0;
}
