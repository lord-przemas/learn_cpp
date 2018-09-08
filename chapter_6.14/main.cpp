#include <iostream>


int main()
{

  int number {123};
  int* ptr {&number};
//  int** ptrptr {&&number}; // Compliler ERROR!

//  int** tbl2d { new int[5][10] }; // Compliler ERROR!

  int (*array_1)[3] = new int[2][3] { {1,2,3}, {4,5,6} };
  auto array_2 = new int[2][3] { {1,2,3}, {4,5,6} };
  int** array_3 { new int*[3]{new int[4]{1,2,3,4}, new int[2]{1,3}, new int[10]{5,2,1}} };
  auto  array_4 { new int*[3]{new int[4]{1,2,3,4}, new int[2]{1,3}, new int[10]{5,2,1}} };

  delete [] array_1;
  delete [] array_2;
  for(int i {}; i < 3; i++)
  {
    delete [] array_3[i];
    delete [] array_4[i];
  }
  delete [] array_3;
  delete [] array_4;
  
  std::cout << std::endl;

// Allocation of 2-dimensional dynamic array
  constexpr unsigned int SIZE_1ST_DIM {5};
  constexpr unsigned int SIZE_2ST_DIM {10};
// Example 1
  int** tbl2d_1 { new int*[SIZE_1ST_DIM] };
  for(int i {}; i < SIZE_1ST_DIM; i++)
    tbl2d_1[i] = new int[SIZE_2ST_DIM];
  
  for(int i {}; i < SIZE_1ST_DIM; i++)
    delete [] tbl2d_1[i];
  delete [] tbl2d_1;

// Example 2
  int* tbl2d_2[SIZE_1ST_DIM];
  for(int i {}; i < SIZE_1ST_DIM; i++)
    tbl2d_2[i] = new int[SIZE_2ST_DIM];

  for(int i {}; i < SIZE_1ST_DIM; i++)
    delete [] tbl2d_2[i];

// Example 3
  int* buffer {new int[SIZE_1ST_DIM * SIZE_2ST_DIM]};
  int** tbl2d_3 { new int*[SIZE_1ST_DIM] };
  int j {};
  for(int i {}; i < SIZE_1ST_DIM * SIZE_2ST_DIM; i += SIZE_2ST_DIM)
    tbl2d_3[j++] = buffer + i;


  for(int i {}; i < SIZE_1ST_DIM; i++)
    for(int j {}; j < SIZE_2ST_DIM; j++)
      tbl2d_3[i][j] = i * j;

  for(int i {}; i < SIZE_1ST_DIM; i++)
  {
    for(int j {}; j < SIZE_2ST_DIM; j++)
      std::cout << tbl2d_3[i][j] << " ";
    std::cout << std::endl;
  }

  delete [] buffer;
  delete [] tbl2d_3;

  return 0;
}
