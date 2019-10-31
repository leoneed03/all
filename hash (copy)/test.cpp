#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>

#include "hashtable.hpp"
TEST(AllTests, thread_test1)
{
    //hashtable::thread_safe_list* list = new hashtable::thread_safe_list();
    int num = 3;
    hashtable::thread_safe_hashtable* ht = new hashtable::thread_safe_hashtable(4,10);
    for ( int i = 0; i < 10; i++) {
       // list->push_back( new hashtable::node( i, new std::string("HIIEE")));
    }
    std::vector<int> vect1 (1000,0);
    std::vector<int> vect2 (1000,0);
    std::vector<int> vect3 (1000,0);
    for (int i = 0; i < 1000; i++) {
        vect1[i] = i;
        vect2[i] = rand() % 1000;
        vect3[i] = rand() % 1000;
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
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









