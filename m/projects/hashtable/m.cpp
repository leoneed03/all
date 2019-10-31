#include "m.hpp"

thread_safe_hashtable::thread_safe_hashtable( int n ): size( n ), table( new std::list<int>[size] ), vect( std::vector<std::mutex>( size )) {}
thread_safe_hashtable::~thread_safe_hashtable(){ 
    delete [] table;
}
void thread_safe_hashtable::insert( int key ) {
    int id = hash_function(key);
    table[id].push_back(key);
}
void thread_safe_hashtable::multi_insert( std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        vect[v[i] % vect.size()].lock();
        insert(v[i]);
        vect[v[i] % vect.size()].unlock();
    }
}
void thread_safe_hashtable::multi_extract(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        vect[v[i] % vect.size()].lock();
        extract(v[i]);
        vect[v[i] % vect.size()].unlock();
    }
}
void thread_safe_hashtable::extract( int key) {
    int id = hash_function(key);
    auto table = this->table;
    std::list<int>::iterator i;
    for ( i = table[id].begin(); i != table[id].end(); i++ ) {
        if (*i == key)
            break;
    }
    if ( i != table[id].end() ) {
        table[id].erase(i);
    }
}
int thread_safe_hashtable::hash_function ( int key ) {
    return ( key % this->size);
}
std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht ) {
    for ( int i = 0; i < ht.size; i++ ) {
    os << i << " ";
    for ( int x : ht.table[i] )
    os << " --> " << x;
    os << std::endl;
    }
    
    os << std::endl;
}

