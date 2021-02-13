// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <iostream>
#include <thread>

// The main idea: to show simple example with std::thread

void hello()
{
    std::cout << "Hello Concurrent World\n";
    
    // Why \n is used instead of std::endl ?
    // Because std::flush (which is included in std::endl) is not necessarry here.
    
    // When std::endl (with std::flush) is necessary ?
    //
    // Example 1:
    //   To display title before some operation like:
    //     std::cout << "Beginning computations..." << std::endl;
                      // without buffer flushing you may encounter a situation when
                      // both lines are displayed at the same time when computations are finished
    //     computations();
    //     std::cout << " done!\n";
    //   https://stackoverflow.com/questions/22026751/c-force-stdcout-flush-print-to-screen
    // 
    // Example 2:
    //   To display a progress bar
    //   https://stackoverflow.com/questions/213907/stdendl-vs-n#comment6217683_214076
    
}

int main()
{
    std::thread t(hello);  // !!HELLO THREAD EXAMPLE!!
    t.join();              //
}

#include <iostream>
#include <thread>

// The main idea: show you the most unpleasant syntax case in C++: parsing temporary object as function declaration

class C
{
public:
    void operator()() const
    {
        std::cout << ++x << std::endl;
    }
private:
  static int x;
};

int C::x = 1;

int main()
{
  std::thread f1(C());    // !!THE MOST UNPLEASANT SYNTAX CASE:!!
                          // You wanted to pass the temporary object C()
                          // (callable temporary object with operator())
                          // but it parsed as function declaration:
                          // double f ( C (*)() );        // C (*)() - pointer to function returning C
                          // Thread is not started here
                 
  std::thread f2((C()));  // ok (Way 1)
                          // Thread is started.
                          // Thread represented by operator() method of temporary object
  
  std::thread f3{C()};    // ok (Way 2)
                          // Thread is started
                          // Thread represented by operator() method of temporary object
                          // {} - syntax of initialization

  C c1;                          
  std::thread f4(c1);     // ok
                          // Thread is started
                          // Thread represented by operator() method of object c1
                          
  
  f2.join();
  f3.join();
  f4.join();  
}

// Output example 1:
// 243
    
// Output example 2:
// 2
// 3
// 4

// Output example 4:
// 23
// 4
