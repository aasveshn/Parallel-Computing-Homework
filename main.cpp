#include <iostream>
#include <thread> 
#include <vector>
#include <chrono>

#include "FirstTask/FirstTask.h"
#include "SecondTask/SecondTask.h"
#include "ThirdTask/ThirdTask.h"
#include "FourthTask/FourthTask.h"


int main()
{
 // FirstTask(1, 20);
 // FirstTask(2, 20);
 // FirstTask(3, 20);
 // FirstTask(4, 20);
 
 // SecondTask(4);
 
  //ThirdTask(1);
  //ThirdTask(2);
  //ThirdTask(3);
  //ThirdTask(4);
  FourthTask(1);
  FourthTask(2);
  FourthTask(3);
  FourthTask(4);

  return 0;
}
