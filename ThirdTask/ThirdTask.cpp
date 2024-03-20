#include "ThirdTask.h"

#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>
#include <chrono>

void bubbleSort(std::vector<int>& arr, const int numThreads) {
    int n = arr.size();
    #pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void ThirdTask(const int numThreads)
{
  auto startTime = std::chrono::high_resolution_clock::now();

  std::vector<int> arr(80000, 0);

  bubbleSort(arr, numThreads);

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
   std::cout << "Number of threads : " << numThreads << "\n";
  std::cout << "Time taken: " << duration << " milliseconds \n \n";
}
