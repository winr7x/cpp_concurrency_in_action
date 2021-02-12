// g++ -Os -Wall -Werror -s src.cpp -pthread -o program

#include <chrono>
#include <iostream>
#include <thread>

// The main idea: with thread programming it is very easy to 
// make mistake and use destroyed variable in working thread

struct func
{
  int& i;
  func(int& i_):i(i_){}
  void operator()()                     // working thread
  {
    for(unsigned j=0;j<1000000;++j)
    {
      std::cout << j << std::endl;
    }
  }
};

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);       // some_local_state is passed by reference
  std::thread my_thread(my_func);
  my_thread.detach();
}

int main()
{
  oops();
  // variable some_local_state is destroyed here
  std::cout << "oops completed" << std::endl;
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2000ns);   // oops() completed, but working thread continues to
                                         // increment destroyed some_local_state
  return 0;
}

// Output:
// oops completed
// 0
// 1
// 2
// 3
// 4
// 5
// 6
// 6
// 7
// 8
// 9
// 10
// 11
// 12
// 13
// 13
