#include "list.hpp"

namespace hashtable {
	thread_safe_list::thread_safe_list( node* nd ): head(nd), size(1) {};
    thread_safe_list::thread_safe_list(): head( new node(MAX, new std::string("NULL")) ), size(0) {};
	thread_safe_list::~thread_safe_list() {
	    auto temp = head; 
		while (temp) {
		    auto next = temp -> get_next();
		    delete temp;
		    temp = next;
		}  
	}
	void thread_safe_list::lock() {
		auto temp = head;
		while (temp) {
			temp -> lock();
		    temp = temp -> get_next();
		}
	}
	void thread_safe_list::unlock() {
		auto temp = head;
		while (temp) {
			temp -> unlock();
			temp = temp -> get_next();
		}
	}
	void thread_safe_list::push_vector( std::vector<int> vect ) {
	    for (int i = 0; i < vect.size(); i++) {
            this -> push_back( new node(vect[i], new std::string("PUSH MUCH")) );
        }
	}
	void thread_safe_list::extract_vector( std::vector<int> vect ) {
	    for (int i = 0; i < vect.size(); i++) {
	        this -> extract_node( vect[i] );
	    }
	}
	void thread_safe_list::check_vector( std::vector<int> vect ) {
	    for (int i = 0; i < vect.size(); i++) {
	        this -> check_for_key( vect[i] );
	    }
	}
	node* thread_safe_list::get_head() {
		return head;
	}
	void thread_safe_list::push_back( node* nd ) {
	    auto curr = head;
	    auto prev = head;
	    prev -> lock();
	    while ((curr = prev -> get_next()) != nullptr) {
	        curr -> lock();
	        prev -> unlock();
	        prev = curr;
	    }
	    prev -> set_next(nd);
	    nd -> set_next( nullptr );
	    prev -> unlock(); 
	    this -> lock();
	    size++;
	    this -> unlock();
	}
	int thread_safe_list::extract_node( int my_key ) {
	    if ( my_key == MAX )
	        return 0;
	    auto curr = head;
	    auto prev = head;
	    prev -> lock(); 
	    while ( (curr = prev -> get_next()) != nullptr ) {
	        curr->lock();
	        if ( (curr -> get_key()) == my_key) {
	            prev -> set_next( curr -> get_next() );
	            prev -> unlock();
	            curr -> unlock();
	            delete curr;
	            this -> lock();
	            size--;
	            this -> unlock();
	            return 1;
	        }
	        prev -> unlock();
	        prev = curr;
	    }
	    prev -> unlock();
	    return 0;
	}
	node* thread_safe_list::check_for_key( int my_key ) {
	    if ( my_key == MAX )
	        return 0;
	    auto curr = head;
	    auto prev = head;
	    prev->lock(); 
	    while ( (curr = prev -> get_next()) != nullptr ) {
	        curr->lock();
	        if ( (curr -> get_key()) == my_key) {
	            prev -> unlock();
	            curr -> unlock();
	            return curr;
	        }
	        prev -> unlock();
	        prev = curr;
	    }
	    prev->unlock();
	    return nullptr;
	}
	void thread_safe_list::check( int key) {
	    if (this -> check_for_key(key))
	        std::cout << key << " - YES";
	    else 
	        std::cout << key << " - NO";
	    std::cout << std::endl;
	}
	
	std::ostream& operator << ( std::ostream& os, const thread_safe_list& list ) {
        os << list.size << ": ";
        auto temp = list.head;
        while (temp) {
            if (temp -> get_key() != MAX)
                os << *temp << " --> ";
            temp = temp -> get_next();
        }
        os << " END" << std::endl;
	}
}
/*
int main(){
    hashtable::thread_safe_list* list = new hashtable::thread_safe_list();
    int num =3;
    for ( int i = 0; i < 10; i++) {
        list->push_back( new hashtable::node( i, new std::string("HIIEE")));
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
    threads[0] = std::thread(&hashtable::thread_safe_list::push_vector, list, std::ref(vect1));
    threads[1] = std::thread(&hashtable::thread_safe_list::extract_vector, list, std::ref(vect2));
    threads[2] = std::thread(&hashtable::thread_safe_list::check_vector, list, std::ref(vect3));
    for (int i = 0 ; i < num; i++) {
        threads[i].join();
    }
    list->check(20);
    list->check(2);
    std::cout << *list;
    delete list;
	return 0;
}*/

