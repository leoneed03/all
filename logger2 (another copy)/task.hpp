#ifndef _TASK_H_INCLUDED
#define _TASK_H_INCLUDED

#include <string>

class task {
	private:
		std::string* str;
	public:
		task( std::string );
		~task();
		std::string* get_str();
		void change_str( std::string new_str);
};
#endif
