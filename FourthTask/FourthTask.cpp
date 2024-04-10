#include "FourthTask.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <chrono>

void fillMatrixRandom(std::vector<std::vector<int>>& a, const int numThreads) {
  srand(time(NULL));

  omp_set_num_threads(numThreads);
  #pragma omp parallel for 
  for (int i = 0; i < a.size(); ++i)
  {
    for (int j = 0; j < a.size(); ++j)
      a[i][j] = rand() % 10;
  }
}

void matrixMultiply(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b,
                    std::vector<std::vector<int>>& c,  const int numThreads) {
    
    omp_set_num_threads(numThreads);
    #pragma omp parallel
    {
        int local_sum; 

        #pragma omp for 
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[0].size(); ++j) {
                local_sum = 0; 
                for (int k = 0; k < a[0].size(); ++k) {
                    local_sum += a[i][k] * b[k][j];
                }
                #pragma omp critical
                c[i][j] += local_sum;
            }
        }
    }
}

void FourthTask(const int numThreads)
{
  auto startTime = std::chrono::high_resolution_clock::now();

  std::vector<std::vector<int>> A(1000, std::vector<int>(1000));
  std::vector<std::vector<int>> B(1000, std::vector<int>(1000));
  std::vector<std::vector<int>> C(1000, std::vector<int>(1000, 0));

  fillMatrixRandom(A, numThreads);
  fillMatrixRandom(B, numThreads);

  matrixMultiply(A, B, C, numThreads);

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
  std::cout << "Number of threads : " << numThreads << "\n";
  std::cout << "Time taken: " << duration << " milliseconds \n \n";
}
