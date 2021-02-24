// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <chrono>
#include <iostream>
#include <thread>

// The main idea: thread and it's argument's converting process can start after
// the original argument has become invalid

using namespace std::chrono_literals;

void f(const double &i, const std::string &s)
{
	// !CONVERTING TO std::string & CAN START WHEN BUFFER IS ALREADY INVALID!
	std::cout << "i == " << i << ", " << "s == '" << s << "'\n";
}

void oops()
{
	char buffer[1024] = {0};
	buffer[0] = '7';
	std::thread t(f, 3, buffer);
	// std::thread t(f, 3, std::string(buffer));    // try this to avoid char* --> std::string conversion
	                                                // and to fix problem
	t.detach();
}

int main()
{
	oops();
	std::cout << "after oops. buffer is invalid\n";
	std::this_thread::sleep_for(50ms);
	return 0;
}

// Output:
// after oops. buffer is invalid
// i == 3, s == '�.ĉ�'

// after oops. buffer is invalid
// i == 3, s == ''

// after oops. buffer is invalid
// i == 3, s == '���zG'