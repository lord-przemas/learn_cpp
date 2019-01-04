#include <cstdio>
#include <cstring>
#include <vector>
#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_allocator.hpp>
#include <boost/align/is_aligned.hpp>

#define OFFSET(NAME, FIELD) (size_t)(&(((NAME*)0)->FIELD))

void printInfo(void* storage, size_t alignment)
{
  printf("address: %p\n", storage);
  printf("address: %d\n", storage == nullptr);

  if(boost::alignment::is_aligned(storage, alignment))
  {
    printf("Memory is aligned to %lu.\n", alignment);
  }
  else
  {
    printf("Warning! Memory is NOT aligned to %lu.\n", alignment);
  }
  printf("--------------------------------\n");
}

int main()
{
 
  constexpr size_t ALIGN {1024 * 128};

  void* storage = boost::alignment::aligned_alloc(ALIGN, 16);
  printInfo(storage, ALIGN);
  boost::alignment::aligned_free(storage);

  std::vector<int, boost::alignment::aligned_allocator<int, ALIGN>> vec {1, 2};
  storage = &vec[0];
  printInfo(storage, ALIGN);
  storage = &vec[1];
  printInfo(storage, ALIGN);

  return 0;
}
