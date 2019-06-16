#include <iostream>
#include <string>
#include "quicksort.h"


int findUniqueCharIndex(const std::string text)
{
  const int textSize = text.size();
  int i;
  for(int k = 0; k < textSize; k++) {
    for(i = 0; text[i] != text[k] && i <= k ; i++);
    if(i != k)
      continue;

    for(i = textSize - 1; text[i] != text[k] && i >= k ; i--);
    if(i != k)
      continue;
    else
      return k;
  }
  return -1;
}

int findUniqueCharIndexV2(const std::string text)
{
  const int textSize = text.size();
  int i;
  for(int k = 0; k < textSize; k++) {
    for(i = 0; i < textSize; i++) {
      if(k == i)
        continue;
      else if(text[k] == text[i])
        break;
    }
    if(i == textSize)
      return k;
  }
  return -1;
}

template <typename T>
int binarySearchIter(T* tbl, int size, T target) {

  int begin {0};
  int end {size - 1};

  while (begin <= end)
  {
    int mindex { (end + begin) / 2 };

    if(target < tbl[mindex])
      end = mindex - 1;
    else if(target > tbl[mindex])
      begin = mindex + 1;
    else
      return mindex;
  }
  return -1;
}

template <typename T>
int binarySearchRecursive(T* tbl, int begin, int end, T target) {
  if(begin > end)
    return -1;

  const int mindex { (end + begin) / 2 };

  if(target < tbl[mindex])
    return binarySearchRecursive(tbl, begin, mindex - 1, target);
  else if(target > tbl[mindex])
    return binarySearchRecursive(tbl, mindex + 1, end, target);
  else
    return mindex;
}

template <typename T>
int rotateBits(T number, int bitCount)
{
  constexpr int numOfBits {sizeof(T)*8};
  return (number << (numOfBits - bitCount)) | (number >> bitCount);
}

void rotateArrayByOne(int tbl[], int size)
{
  int last {tbl[size - 1]};
  for(int i {size - 1}; i > 0; i--) {
    tbl[i] = tbl[i - 1];
  }
  tbl[0] = last;
}


template <typename T>
void rotateArray(T tbl[], int size, int numCount)
{
  numCount %= size;
  T last[numCount];
  int k {};
  for(int i {size - numCount}; i < size; i++)
    last[k++] = tbl[i];

  for(int i {1}; i <= numCount; i++){
    for(int j {size - i}; j >= numCount; j -= numCount){
      tbl[j] = tbl[j - numCount];
    }
  }

  for(int k {}; k < numCount; k++)
    tbl[k] = last[k];
}


int main()
{

  // *** Rotate array
  using T = int;
  T tbl[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
  constexpr int size {sizeof(tbl) / sizeof(T)};

  rotateArray(tbl, size, size + 4);

  for(auto num : tbl)
    std::cout << num << std::endl;

  //  // *** Rotate bits
  //  uint32_t bits { 0x11aa66cc };
  //  std::cout << std::hex << "0x" << bits << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 4) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 8) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 12) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 16) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 32) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 36) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 40) << std::endl;
  //  std::cout << std::hex << "0x" << rotateBits(bits, 44) << std::endl;


  //  // *** Binary search
  //  using T = int;
  //  constexpr T target {7};
  //  T tbl[] { 6, 3, 6, 2, 12, 4, 14, 7, 8, 9, 8, 3, 1, 12, 3, 5, 16};
  //  constexpr unsigned int size { sizeof(tbl) / sizeof(T) };
  //  sort::quicksort(tbl, 0, size, ASC);
  //  auto index = binarySearchIter(tbl, size, target);
  //  std::cout << "Index: " << index << std::endl;
  //  index = binarySearchRecursive(tbl, 0, size - 1, target);
  //  std::cout << "Index: " << index << std::endl;
  //
  //
  //  // *** Quick sort
  //  int tbl[] { 6, 3, 6, 2, 12, 4, 14, 7, 8, 9, 8, 3, 1, 12, 3, 5, 16};
  //  sort::quicksort(tbl, 0, sizeof(tbl) / sizeof(int), ASC);
  //
  //  for(auto e : tbl)
  //    std::cout << e << ", ";
  //
  //  std::cout << std::endl;


  //// *** Find index of unique character
  //  const std::string text1 {"Hello Henry"};
  //  std::cout << findUniqueCharIndex(text1) << std::endl;
  //
  //  const std::string text2 {"HelloHello"};
  //  std::cout << findUniqueCharIndex(text2) << std::endl;
  //
  //  const std::string text3 {"aaaaaaaaaaaaa"};
  //  std::cout << findUniqueCharIndex(text3) << std::endl;
  //
  //  const std::string text4 {"aa"};
  //  std::cout << findUniqueCharIndex(text4) << std::endl;
  return 0;
}
