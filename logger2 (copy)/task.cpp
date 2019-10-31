#include "task.hpp"

task::task( std::string new_str): str( new std::string(new_str) ) {} ;
task::~task() {
	delete str;
}
std::string* task::get_str() {
	return str;
}
void task::change_str(std::string new_str) {
	delete str;
	str = new std::string(new_str);
	return;
}
