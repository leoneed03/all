#include "m.hpp"

thread_safe_hashtable::thread_safe_hashtable( int n ): size( n ), factor(4), number_of_elements(0), table( new std::list<int>[size] ), vect( std::vector<std::mutex>( size )) {}
thread_safe_hashtable::~thread_safe_hashtable(){ 
    delete [] table;
}
void thread_safe_hashtable::put_help( int key ) {
    int id = hash_function(key);
	table[id].push_back(key);
	mtx.lock();
    number_of_elements++;
    mtx.unlock();
}
void thread_safe_hashtable::put( int key ) {
    vect[ key % vect.size() ].lock();
    put_help(key);
    vect[ key % vect.size() ].unlock();
}
void thread_safe_hashtable::get_help( int key, std::vector<int> &v ) {
    int id = hash_function(key);
    auto table = this->table;
    std::list<int>::iterator i;
    for ( i = table[id].begin(); i != table[id].end(); i++ ) {
        v.push_back(*i);
    }
    return;
}
void thread_safe_hashtable::get( int key, std::vector<int> &v) {
    vect[ key % vect.size()].lock();
    get_help(key, v);
    vect[ key % vect.size()].unlock();
}
void thread_safe_hashtable::multi_put( const std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        put(v[i]);
    }
}
void thread_safe_hashtable::lock_all() {
    for (int  i = 0; i < vect.size(); i++) {
        vect[i].lock();
    }
}
void thread_safe_hashtable::unlock_all() {
    for (int  i = 0; i < vect.size(); i++) {
        vect[i].unlock();
    }
}
int thread_safe_hashtable::check( int key ) {
    vect[ key % vect.size() ].lock();
    int res = check_help(key);
    vect[ key % vect.size() ].unlock();
    return res;
}
std::list<int>::iterator thread_safe_hashtable::get_it( int key ) {
    int id = hash_function(key);
    auto table = this->table;
    std::list<int>::iterator i;
    for ( i = table[id].begin(); i != table[id].end(); i++ ) {
        if (*i == key)
            break;
    }
    return i;
}
int thread_safe_hashtable::check_help( int key ) {
    int id = hash_function(key);
    auto i = get_it(key);
    if ( i != table[id].end() )
        return 1;
    else 
        return 0;
}
int thread_safe_hashtable::hash_function ( int key ) {
    return ( key % this->size);
}
std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht ) {
    for ( int i = 0; i < ht.size; i++ ) {
    os << i << " ";
    for ( int x : ht.table[i] )
    os << " - " << x;
    os << std::endl;
    }
    
    os << std::endl;
}

