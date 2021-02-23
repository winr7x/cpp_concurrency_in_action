// g++ -Os -Wall -Werror -s -std=c++17 src.cpp -pthread -o program

#include <chrono>
#include <iostream>
#include <thread>

// The main idea: each thread runs the same code but with different data 

char number = '1';

enum command_type {
	open_new_document
};

struct user_command
{
	command_type type;

	user_command(): type(open_new_document)
	{
	}
};

bool done_editing()
{
	return number > '3';
}

void process_user_input(user_command const& cmd)
{
}

std::string get_filename_from_user()
{
	return std::string("doc") + number++;
}

user_command get_user_input()
{
	return user_command();
}

void open_document_and_display_gui(const std::string& filename)
{
	std::cout << "opened document '" << filename << "'\n";
}

void edit_document(std::string const& filename)				// !THE SAME CODE IS EDIT_DOCUMENT()!
								 	// !DIFFERENT DATA IS FILENAME!
{
	open_document_and_display_gui(filename);
	while(!done_editing())
	{
		user_command cmd=get_user_input();
		if (cmd.type == open_new_document) {
			std::string const new_name = get_filename_from_user();
			std::thread t(edit_document, new_name);		// !THE SAME CODE IS EDIT_DOCUMENT()!
			t.detach();
		} else {
		  process_user_input(cmd);
		}
	}
}

int main()
{
	edit_document(get_filename_from_user());			// !THE SAME CODE IS EDIT_DOCUMENT()!
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(50ms);
	return 0;
}

// Output:
// opened document 'doc1'
// opened document 'doc2'
// opened document 'doc3'
