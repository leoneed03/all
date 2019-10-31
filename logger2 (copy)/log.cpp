#include "log.hpp"
logger::logger(){}
void logger::worker_thread_func(int id, task* new_task) {
	{
		std::lock_guard<std::mutex> g_lock(mtx_print);
		std::ofstream out( "", std::ios::app );
		if (out.is_open()) {
			out << "thread #" << id << "started working" << std::endl;
		}
		out.close();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1 + rand() % 100));
	{
		std::lock_guard<std::mutex> g_lock(mtx_print);
		std::ofstream out( "", std::ios::app );
		if (out.is_open()) {
			out << "thread #" << id << "pushed notification ";
			if (*(task.str))
				out << (*(task.str));
			out << std::endl;
		}
		out.close();
	}
	{
		std::lock_guard<std::mutex> g_lock(mtx_queue);
		tasks.push(new_task);
		notified = true;
		cv.notify_one();
	}
}
void logger::logger_thread_func() {
	while (!shut_down) {
		std::unique_lock<std::mutex> u_lock(mtx_queue);
		while (!notified)
			cv.wait(u_lock);
		while (!tasks.empty) {
			std::lock_guard<std::mutex> g_lock(mtx_print);
			std::ofstream out( "", std::ios::app );
			if (out.is_open()) {
				if (*(task.str))
					out << (*(task.str));
				out << std::endl;
		 	}
			out.close();
			tasks.pop();
		}
	}
}
int main() {
	int num = 10;
	std::thread l_thread(logger_func);
	std::vector<thread> w_threads();
	for ( int i = 0; i < num; i++ )
		w_threads[i] = std::thread(worker_thread_func, i, new task(" Hi.. "));
	for ( int i = 0; i < num; i++)
		w_threads[i].join();
	shut_down = true;
	l_thread.join();
	return 0;
}


