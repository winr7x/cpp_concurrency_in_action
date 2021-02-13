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
