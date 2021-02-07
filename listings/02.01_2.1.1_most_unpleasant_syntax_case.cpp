#include <iostream>
#include <thread>

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
  std::thread f1(C());    // The most unpleasant syntax case:
                          // You wanted to pass the temporary object C()
                          // (callable temporary object with operator())
                          // but it parsed as function declaration:
                          // double f ( C (*)() );
                          // Thread is not started here
                 
  std::thread f2((C()));  // ok (Way 1)
                          // Thread is started.
                          // Thread represented by operator() method of temporary object
  
  
  std::thread f3{C()};    // ok (Way 2)
                          // Thread is started
                          // Thread represented by operator() method of temporary object

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
