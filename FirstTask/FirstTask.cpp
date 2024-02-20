#include "FirstTask.h"

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void CalculateFactorianl(uint64 startNumber, uint64 finishNumber, uint64& result)
{
  for (uint64 i = startNumber; i < finishNumber; ++i)
    result *= i;
}

void FirstTask(const int numThreads, uint64 number)
{
  std::vector<std::thread> threads(numThreads);
  std::vector<uint64> results(numThreads, 1);
  const uint64 numbersForThread = number / numThreads;

  auto startTime = std::chrono::high_resolution_clock::now();
  for (uint64 i = 0; i < numThreads; ++i)
  {
    uint64 start = 1 + i * numbersForThread;
    uint64 end = (i == numThreads - 1) ? number + 1 : start + numbersForThread;
    threads[i] = std::thread(CalculateFactorianl, start, end, std::ref(results[i]));
  }

  for (auto& thread : threads)
    thread.join();

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

  uint64 totalResult = 1;
  for (const auto& result : results)
    totalResult *= result;

  std::cout << "Number of threads : " << numThreads << "\n";
  std::cout << "Factorail of : " << number << "\n";
  std::cout << "Result : " << totalResult << "\n";
  std::cout << "Time taken: " << duration << " nanoseconds \n \n";
}
