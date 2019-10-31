#include "node.hpp"

namespace hashtable {
	node::node( int new_key, std::string* new_str ): key(new_key), str(new_str), prev(nullptr), next(nullptr) {};
	node::node( const node& nd ): key(nd.key), str(new std::string( *(nd.str) )), prev(nullptr), next(nullptr) {};
	node::~node() { 
		delete str;
	}
	void node::lock() {
		mtx.lock();
	}
	void node::unlock() {
		mtx.unlock();
	}
	void node::set_key( int new_key ) {
		key = new_key;
	}
	void node::set_str( std::string* new_str ) {
		delete str;
		str = new_str;
	}
	void node::set_next( node* nd ) {
		next = nd;
	}
	void node::set_prev( node* nd ) {
		prev = nd;
	}
	int node::get_key() {
		return key;
	}
	std::string* node::get_str() {
		return str;
	}
	node* node::get_next() {
		return next;
	}
	node* node::get_prev() {
		return prev;
	}
	std::ostream& operator << ( std::ostream& os, const node& nd ) {
    os << nd.key << " ";
    if (nd.str) 
    	os << *(nd.str) << " ";
    else 
    	os << " ";
	}
    /*class node {
        private:
            std::mutex mtx;
            int key;
            std::string str;
            node* next;
            
            friend std::ostream& operator << ( std::ostream& os, const node& nd );
        public: 
            node(int, std::string);
            ~node();
            void mute_node();

            
    };
    std::ostream& operator << ( std::ostream& os, const thread_safe_list& list );*/
    

}/*
int main(){
	return 0;
}*/

