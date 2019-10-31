#include "hashtable.hpp"
#include <vector>
namespace hashtable {
	//thread_safe_hashtable::thread_safe_hashtable( int fact, int my_size ): factor(fact), size(my_size), number_of_elements(0), vect( new std::vector<thread_safe_list*>(my_size, new thread_safe_list())) {};
	thread_safe_hashtable::thread_safe_hashtable( int fact, int my_size ) {
		factor = fact;
		size = my_size; 
		number_of_elements = 0;
		vect = new std::vector<thread_safe_list*>(my_size);
		for (int i = 0; i < my_size; i++) {
			(*vect)[i] = new thread_safe_list();
}
	}
	thread_safe_hashtable::~thread_safe_hashtable() {
		for (int i = 0; i < size; i++) {
			delete (*vect)[i];
		} 
		delete vect;
	}
	void thread_safe_hashtable::lock() {
		mtx.lock();
	}
	void thread_safe_hashtable::lock_all() {
		for (int i = 0; i < size; i++) 
			(*vect)[i]->lock();
	}
	void thread_safe_hashtable::unlock_all() {
		for (int i = 0; i < size; i++)
			(*vect)[i]->unlock();
	} 
	void thread_safe_hashtable::unlock() {
		mtx.unlock();
	}
	void thread_safe_hashtable::check_for_rehash() {
		lock_all();
		if (number_of_elements / size > factor)
			rehash();
		std::cout<<"GOOD"<<std::endl;
		unlock_all();
	}
	void thread_safe_hashtable::rehash() {
		std::vector<thread_safe_list*> lists(size);
		for (int i = 0; i < size; i++) {
			lists[i] = (*vect)[i];
			(*vect)[i] = new thread_safe_list();
			(*vect).push_back(new thread_safe_list());
		}
		number_of_elements = 0;
		size = 2 * size;
		std::cout<<*this;
		std::cout<<"HERE"<<std::endl;
		for (int i = 0; i < lists.size(); i++) {
			std::cout<<i<<std::endl;
			auto temp = lists[i] -> get_head() -> get_next();
			std::cout<<i<<std::endl;
			while (temp) {
				std::cout<<"temp "<<std::endl;
				auto help = temp -> get_next();
				temp -> set_next(nullptr);
				(*vect)[ hash(temp -> get_key()) ] -> push_back_help(temp);
				std::cout<<i<<std::endl;
				//temp -> set_next(nullptr);
				temp = help;
				std::cout<<i<<std::endl;
			}
			
		}
	}
	void thread_safe_hashtable::push_vector( std::vector<int> my_vect ) {
		for (int i = 0; i < my_vect.size(); i++) {
			this -> push( new node(my_vect[i], new std::string("HT")) );
		}
		check_for_rehash();
	}
	void thread_safe_hashtable::extract_vector( std::vector<int> vect ) {
	    for (int i = 0; i < vect.size(); i++) {
	        this -> extract( vect[i] );
	    }
	}
	void thread_safe_hashtable::check_vector( std::vector<int> vect ) {
	    for (int i = 0; i < vect.size(); i++) {
	        this -> check( vect[i] );
	    }
	}
	int thread_safe_hashtable::hash( int key) {
		return (key % size);
	}
	void thread_safe_hashtable::push( node* nd ) {
	    (*vect)[ hash(nd->get_key()) ]->push_back(nd);
	    //std::cout<<"PUSHING IN PROCESS"<<std::endl;
	    this -> lock();
	    number_of_elements++;
	    this -> unlock();
	}
	int thread_safe_hashtable::extract( int my_key ) {
	    int res = (*vect)[ hash(my_key) ]->extract_node(my_key);
	    this -> lock();
	    number_of_elements -= res;
	    this -> unlock();
	}
	node* thread_safe_hashtable::check( int my_key ) {
	    return (*vect)[ hash(my_key) ]->check_for_key(my_key);
	}
	void thread_safe_hashtable::check_YES_NO( int my_key) {
	    if ((*vect)[hash(my_key)] -> check_for_key(my_key))
	        std::cout << my_key << " - YES";
	    else 
	        std::cout << my_key << " - NO";
	    std::cout << std::endl;
	}

	std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht ) {
		os << (*ht.vect).size() << std::endl;
		for (int i = 0; i < ht.size; i++ ) {
			os << "THIS IS " << i << ":   ";
			thread_safe_list* x = (*(ht.vect))[i];
			os << *x;
			os << std::endl << "ENDED" << std::endl;
		}
	}
}
/*
int main(){
    //hashtable::thread_safe_list* list = new hashtable::thread_safe_list();
    int num = 3;
    hashtable::thread_safe_hashtable* ht = new hashtable::thread_safe_hashtable(4,10);
    for ( int i = 0; i < 10; i++) {
       // list->push_back( new hashtable::node( i, new std::string("HIIEE")));
    }
    std::vector<int> vect1 (100,0);
    std::vector<int> vect2 (100,0);
    std::vector<int> vect3 (100,0);
    for (int i = 0; i < 100; i++) {
        vect1[i] = i;
        vect2[i] = i + 20;
        vect3[i] = i + 100;
    }
    int j = 0;
    std::thread threads[num];
    for ( int i = 0; i < num; i++) {
       // hashtable::node* new_node = new hashtable::node(i * 100 + j, new std::string("ME"));
        //threads[i] = std::thread(&hashtable::thread_safe_list::push_vector, list, std::ref(vect1));
        //j++;
    }
    threads[0] = std::thread(&hashtable::thread_safe_hashtable::push_vector, ht, std::ref(vect1));
    //threads[0] = std::thread(&hashtable::thread_safe_hashtable::push_vector, ht, std::ref(vect1));
    threads[1] = std::thread(&hashtable::thread_safe_hashtable::extract_vector, ht, std::ref(vect2));
    threads[2] = std::thread(&hashtable::thread_safe_hashtable::check_vector, ht, std::ref(vect3));
    for (int i = 0 ; i < 3; i++) {
        threads[i].join();
    }
    //list->check(20);
    //list->check(2);
    std::cout << *ht;
    std::cout << "!!!!";
    delete ht;
	return 0;
}
*/
