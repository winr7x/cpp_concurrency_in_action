// g++ -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <iostream>
#include <thread>

// The thread object can be joined only once

int main()
{
  std::thread t1([]{
    std::cout << "lambda function\n";
  });
  
  std::cout << "t1.joinable() == " << t1.joinable() << '\n';
  
  t1.join(); // after join t1 can not be joined again
  
  std::cout << "t1.joinable() == " << t1.joinable() << '\n';
  
  t1.join(); // but we blocked here (why?)
  
  // unreachable code
}

// Output example 1:
// t1.joinable() == 1
// 1st lambda function
// t1.joinable() == 0
    
