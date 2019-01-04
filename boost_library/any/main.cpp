#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/any.hpp>

using boost::any_cast;
typedef std::vector<boost::any> many;

void append_int(many & values, int value)
{
    boost::any to_append = value;
    values.push_back(to_append);
}

void append_string(many & values, const std::string & value)
{
    values.push_back(value);
}

void append_char_ptr(many & values, const char * value)
{
    values.push_back(value);
}

void append_any(many & values, const boost::any & value)
{
    values.push_back(value);
}

void append_nothing(many & values)
{
    values.push_back(boost::any());
}


int main()
{
  many values {};
  append_int(values, 123);
  append_string(values, "std::string object");
  append_char_ptr(values, "char pointer");
  append_int(values, 456);
  append_int(values, 789);

  auto is_int = [](const boost::any& o)
  {
    return (o.type() == typeid(int));
  };

  auto is_string = [](const boost::any& o)
  {
    return (o.type() == typeid(std::string));
  };

  int count_int = std::count_if(values.begin(), values.end(), is_int);
  std::cout << "count_int: " << count_int << std::endl;
  
  for(auto e : values)
  {
    if(is_int(e))
      std::cout << "value: " << boost::any_cast<int>(e) << std::endl;
    else if(is_string(e))
      std::cout << "value: " << boost::any_cast<std::string>(e) << std::endl;
  }

  return 0;
}
