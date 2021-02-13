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

// The main idea: it is important to take care of the guaranteed join() call
// even if an exception is thrown

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

void f()
{
        int some_local_state=0;
        func my_func(some_local_state);
        std::thread t(my_func);
        try
        {
                do_something_in_current_thread();                          // without try-catch there is a chance to terminate
                                                                           // program without calling thread joining. it is bad
        }
        catch(...)
        {
                std::cout << "join() in catch section" << std::endl;
                t.join();                                                  // !!GUARANTEED JOIN() CALL!!
                throw;
        }
        std::cout << "normal join()" << std::endl;
        t.join();                                                          // !!GUARANTEED JOIN() CALL!!
}

int main()
{
        try { f(); }catch(...){}
        return 0;
}

// Output:
// join() in catch section
