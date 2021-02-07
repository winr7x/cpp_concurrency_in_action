#include <iostream>

class C
{
public:
    void operator()() const
    {
    }
};

int main()
{
  double f(C());     // compilation ok
                     // you declare a function: arg is TODO
                 
  double f((C()));   // compilation failure. TODO
  
  
  double f({C()});   // compilation failure. TODO
}
