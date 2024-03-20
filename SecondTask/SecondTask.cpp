#include "SecondTask.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mutex;
int sharedData = 0;

void updateSharedData(int threadId) {

    for (int i = 0; i < 5; ++i) {
        sharedData += 10;
        std::cout << "Thread " << threadId << ": Shared data updated to " << sharedData << "\n";
    }
}

void updateSharedDataWithMutex(int threadId) {
  std::lock_guard<std::mutex> lock(mutex);
    for (int i = 0; i < 5; ++i) {
        sharedData += 10;
        std::cout << "Thread " << threadId << ": Shared data updated to " << sharedData << "\n";
    }
}

void SecondTask(const int numThreads)
{
  std::vector<std::thread> threads(numThreads);

  std::cout << "Processing shared data without mutex: \n";

  for (int i = 0; i < numThreads; ++i) 
      threads[i] = std::thread(updateSharedData, i);
 
  for(auto& thread : threads)
    thread.join();
 
  sharedData = 0;
  std::cout << "\nProcessing shared data with mutex: \n";

  std::vector<std::thread> threadsWithMutex(numThreads);

  for (int i = 0; i < numThreads; ++i) 
    threadsWithMutex[i] = std::thread(updateSharedDataWithMutex, i);
  
  for(auto& thread : threadsWithMutex)
    thread.join();
}