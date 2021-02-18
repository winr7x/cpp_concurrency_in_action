// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <iostream>
#include <thread>

// The main idea: you can call detach() only when some code is bound to thread

int main()
{
  std::thread t;                       // t without thread-code
  std::cout << "before detach()\n";
  //t = std::thread([]{});             // if assign lambda function code to thread
                                       // then detach() will be called normally
  try {
    t.detach();
  } catch(...) {
    std::cout << "exception\n";        // !!EXCEPTION IS CAUGHT BECAUSE t IS NOT BOUND TO ANY CODE!!
  }
  std::cout << "after detach()\n";
  return 0;
}

// Output:
// before detach()
// exception
// after detach()
