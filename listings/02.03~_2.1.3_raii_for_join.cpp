// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <iostream>
#include <thread>

// The main idea: you can use RAII to simplify code which
// call join() guaranteed, even after exception

void do_something_in_current_thread()
{
  throw std::logic_error("some exception for example");
}

struct func
{
  int& i;
  func(int& i_):i(i_){}
  void operator()()
  {
    for(unsigned j=0;j<1000000;++j)
    {
      // do_something(i);
    }
  }
};

class thread_guard
{
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_):
    t(t_)
  {}
  ~thread_guard()
  {
    if (t.joinable())         // here we envisage case if join() was called somewhere earlier in f()
    {
      std::cout << "calling join()..." << std::endl;
      t.join();
    }
  }
  thread_guard(thread_guard const&)=delete;
  thread_guard& operator=(thread_guard const&)=delete;
};

void f()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);                 // !!F() CODE IS SIMPLE!! only single line
                                     // for guaranteed join() call
  do_something_in_current_thread();
}

int main()
{
  try { f(); }catch(...) {
    std::cout << "The f() function was with an exception" << std::endl;
  }
  return 0;
}

// Output:
// calling join()...
// The f() function was with an exception 
