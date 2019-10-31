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
	private: 
		std::condition_variable cv;
		std::mutex mtx_print;
		std::mutex mtx_queue;
		std::queue<task*> tasks;
		bool shut_down;
		bool notifeid;
	public:
		logger();
		void worker_thread_func(int, task&);
		void logger_thread_func();
		
}
