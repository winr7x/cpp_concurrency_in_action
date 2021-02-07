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
  double f(C());     // The most unpleasant syntax case:
                     // You wanted to pass a temporary object,
                     // but it parsed as function declaration:
                     // double f ( TODO type );
                 
  double f((C()));   // compilation failure. 
                     // error: cannot convert 'C' to 'double' in initialization
  
  
  double f({C()});   // compilation failure.
                     // error: cannot convert '<brace-enclosed initializer list>' to 'double' in initialization
}
