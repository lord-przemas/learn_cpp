#include <iostream>
#include <memory>
#include <algorithm>

class Data
{
  public:

    int x {123};

    Data() = default;
    Data(int num)
    : x {num} 
    {
    }

    Data(const Data& data) 
    : x { data.x } 
    {
      std::cout << "Data(const Data& data)" << std::endl;
    }

    Data(Data&& data) 
    : x { data.x } 
    {
      std::cout << "Data(Data&& data)" << std::endl;
    }

    void operator=(const Data& data) {
      std::cout << "operator=(const Data& data)" << std::endl;
    }

    ~Data() {
      std::cout << "~Data()" << std::endl;
    }
};


int main()
{
  constexpr uint32_t SIZE { 3 }; 

  std::cout << "------ Simple copy ------" << std::endl;
  {
    Data tbl1 [SIZE];
    Data tbl2 [SIZE];

    std::copy(tbl1, tbl1 + std::size(tbl1), tbl2);
  }

  std::cout << "------ Uninitialized copy ------" << std::endl;
  {
    Data data_src [SIZE] {11, 22, 33};
    constexpr uint32_t BUF_SIZE { sizeof(Data) * SIZE }; 
    uint8_t buffer1[BUF_SIZE];
    Data* data_dest = reinterpret_cast<Data*>(buffer1);

    std::uninitialized_copy(data_src, data_src + SIZE, data_dest);
//    std::uninitialized_fill(data_dest, data_dest + SIZE, data_src[1]);
//    std::uninitialized_default_construct(data_dest, data_dest + SIZE);
//    std::uninitialized_move(data_src, data_src + SIZE, data_dest);

    for(int i {}; i < SIZE; i++)
      std::cout << data_dest[i].x << ", ";
    std::cout << std::endl;

    std::destroy(data_dest, data_dest + SIZE);
  }

  return 0;
}
