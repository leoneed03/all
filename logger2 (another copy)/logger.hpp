#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include "task.hpp"

class logger {
	public: 
		std::condition_variable cv1;
		std::condition_variable cv2;
		std::mutex mtx_print_log;
		std::mutex mtx_print_file;
		std::mutex mtx_queue;
		std::mutex mtx_flag;
		std::mutex mtx_size;
		std::queue<task*> tasks;
		int max_size;
		int size;
		bool shut_down;
	public:
		logger();
		void worker_thread_func(int, task*);
		void logger_thread_func();
		void test_func(int, task*);
};
