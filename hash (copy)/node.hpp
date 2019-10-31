#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>

namespace hashtable {
    class node {
        private:
            std::mutex mtx;
            int key;
            std::string* str;
            node* prev;
            node* next;
            
            
            friend std::ostream& operator << ( std::ostream& os, const node& nd );
        public: 
            node(int, std::string*);
            node(const node&);
            ~node();
            void lock();
            void unlock();
            void set_key(int);
            void set_str(std::string*);
            void set_next(node*);
            void set_prev(node*);
            int get_key();
            std::string* get_str();
            node* get_next();
            node* get_prev();

            
    };
    std::ostream& operator << ( std::ostream& os, const node& nd );
}
#endif
