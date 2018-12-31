#include <iostream>
#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
using namespace boost::accumulators;


int main()
{
//  using Type = double;
//  std::vector<Type> vec {1.23, 2.56, 3.234, 4.756, 5.86}; 
//
//  accumulator_set<Type, features<tag::mean, tag::moment<2>, tag::min, tag::max > > acc;
//  acc = std::for_each(vec.begin(), vec.end(), acc);
//
//  // Display the results ...
//  std::cout << "Mean:   " << mean(acc) << std::endl;
//  std::cout << "Moment: " << moment<2>(acc) << std::endl;
//  std::cout << "Min:   " << min(acc) << std::endl;
//  std::cout << "Max:   " << max(acc) << std::endl;
//  std::cout << std::endl;
//  std::cout << "Mean:   " << extract_result<tag::mean>(acc) << std::endl;
//  std::cout << "Moment: " << extract_result<tag::moment<2>>(acc) << std::endl;
//  std::cout << "Min:   " << extract_result<tag::min>(acc) << std::endl;
//  std::cout << "Max: " << extract_result<tag::max>(acc) << std::endl;


  using Type = int;
  std::vector<Type> vec {1, 2, 3, 4, 5}; 

  accumulator_set<Type, features<tag::mean, tag::weighted_mean, tag::min >, Type > acc;

  acc(1, weight = 2);
  acc(2, weight = 4);
  acc(3, weight = 6);

  // Display the results ...
  std::cout << "Mean:   " << extract_result<tag::mean>(acc) << std::endl;
  std::cout << "Weighted Mean:   " << extract_result<tag::weighted_mean>(acc) << std::endl;
  std::cout << "Min:   " << extract_result<tag::min>(acc) << std::endl;

  return 0;
}
