#include "logger.hpp"
logger::logger(){
    shut_down = false;
    max_size = 5;
    size = 0;
}
void logger::worker_thread_func(int id, task* new_task) {
	{
		std::lock_guard<std::mutex> g_lock(mtx_print_log);
		std::ofstream out( "logger.txt", std::ios::app );
		if (out.is_open()) {
			out << "thread #" << id << " pushed notification ";
			out << std::endl;
		}
		out.close();
	}
	{
		std::unique_lock<std::mutex> u_lock(mtx_queue);
		
		while (size >= max_size) {
			u_lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1 + rand() % 10));
			u_lock.lock();
			
			cv1.notify_all();
			//std::cout<<"waiting"<<std::endl;
			}
		
			//cv2.wait(g_lock);
		
		//std::unique_lock<std::mutex> g_lock(mtx_size);
		size++;
		//std::cout<<"+1: "<<size<<std::endl;
		tasks.push(new_task);
		//g_lock.unlock();
		cv1.notify_all();
		//std::cout<<" "<<size<<std::endl;
	}
}
void logger::logger_thread_func() {
	while (true) {
		
		//std::cout<<"Already "<<size<<std::endl;
	    {
	        std::lock_guard<std::mutex> h_lock(mtx_flag);
	        if (shut_down)
	            return;
	    }
	    //std::cout<<"before 1 u "<<size<<std::endl;
	    std::unique_lock<std::mutex> u_lock(mtx_queue);
		//std::cout<<"after 1 u "<<size<<std::endl;
		//while (!shut_down && !tasks.empty())
		    cv1.wait(u_lock);
		
		//std::cout<<"after wait cv1 "<<size<<std::endl;
		//std::unique_lock<std::mutex> gent_lock(mtx_size);    
		//std::cout<<"after 2 u "<<size<<std::endl;
		while (!tasks.empty()) {
			std::unique_lock<std::mutex> g_lock(mtx_print_file);
			std::ofstream out( "out.txt", std::ios::app );
			if (out.is_open()) {
				if ((tasks.front()))
					out << (*( (tasks.front()) -> get_str() ));
				out << std::endl;
		 	}
			out.close();
			//std::cout<<"Now there is "<< size <<std::endl;
			//std::cout<<"NOw only "<< size <<std::endl;
			delete tasks.front();
			tasks.pop();
			size--;
			//std::cout<<"-1: "<<size<<std::endl;
			//cv2.notify_all();
		}
	}
}
void logger::test_func( int id, task* new_task ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1 + rand() % 10));
        worker_thread_func(id, new_task);
}
int main() {
	int num = 100;
	logger* my_logger = new logger();
	std::fstream in("logger.txt", std::ios::out);
	in.close();
	std::fstream out("out.txt", std::ios::out);
	out.close();
	in.open("logger.txt", std::ios::out | std::ios::in);
	if (in.is_open()) {
	    in << "YES!! " << std::endl;
	}
	std::thread l_thread(&logger::logger_thread_func, my_logger);
	std::vector<std::thread> w_threads(num);
	for ( int i = 0; i < num; i++ )
		w_threads[i] = std::thread(&logger::test_func, my_logger, i, new task(" this is the task "));
	for ( int i = 0; i < num; i++)
		w_threads[i].join();
    {
        std::unique_lock<std::mutex> u_lock(my_logger->mtx_queue);
        std::lock_guard<std::mutex> g_lock(my_logger->mtx_flag);
	    my_logger->shut_down = true;
	    (my_logger->cv1).notify_one();
	}
	l_thread.join();
	delete my_logger;
	return 0;
}


