// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <iostream>
#include <chrono>
#include <thread>

// The main idea: without join() or detach() thread object calls
// std::terminate in its destructor and all the program exits

using namespace std::chrono_literals;

void my_func()
{
  for(unsigned j=0;j<1000;++j) {
    std::this_thread::sleep_for(1ms);
    std::cout << "thread: " << j << " iteration\n";
  }
};

void f()
{
  std::thread t(my_func);
  std::this_thread::sleep_for(4ms);
                                         // !!T IS DESTROYED HERE AND STD::TERMINATED IS CALLED!!
                                         // all the program ends here
}

int main()
{
  f();                                   // all the program ends in f()
  std::cout << "main() completed\n";     // this line is unreachable
  return 0;
}

// Output:
// thread: 0 iteration
// thread: 1 iteration
// thread: 2 iteration
