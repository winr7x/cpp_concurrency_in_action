// g++ -Os -s -Wall -Wextra -std=c++17 file.cpp -pthread -o program

#include <iostream>
#include <chrono>
#include <thread>

// The main idea: you can use lambda expression with std::thread

int main()
{
  // Lambda thread function example
  std::thread t([]{
      std::cout << "in thread" << std::endl;
  });
  // You must decide attach or detach thread at the time of creation
  t.detach();
  
  // Sleep 50ms
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  
  // Sleep 50ms
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(50ms);
}

// Output:
// in thread
