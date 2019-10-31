#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include "m.hpp"

int number_of_threads = 4;
void get_minor(const std::vector<std::vector <int>> &matrix, std::vector< std::vector <int>> &new_matrix, int k, int p) {
    int size = matrix.size();
    int counter_2 = 0, counter_1 = 0;
    for (int i = 0; i < size - 1; i++) {
        if (i == k) {
            counter_1++;
        }
        for (int j = 0; j < size - 1; j++) {
            if (j == p) {
                counter_2++;
            }
            new_matrix[i][j] = matrix[i + counter_1][j + counter_2];
        }
        counter_2 = 0;
    }
}

void print_matrix (const std::vector< std::vector <int>> &matrix) {
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix [i][j] << "\t " ;
        }
        std::cout << std::endl;
    }
}
void calculate_minor( const std::vector< std::vector <int>>& matrix, int &res ) {
	int size = matrix.size();
	if ( size == 1 ) {
		res = matrix[0][0];
        return;
    }
    std::vector< std::vector <int>> minor_matrix(size - 1, std::vector<int>(size - 1, 0) ); 
	for ( int i = 0; i < size; i++ ) {
        get_minor(matrix, minor_matrix, 0, i);
        int minor = 0;
	        calculate_minor(minor_matrix, minor);
	    if ( i % 2 == 0 ) {
            res += minor * matrix[0][i];
		} 
       else {
            res -= minor * matrix[0][i];
	   }
    }
}
void calculate_one_thread(const std::vector< std::vector <int>> &matrix, int &res) {
    int size = matrix.size();
    if (size == 1){
        res = matrix[0][0];
        return;
    }
    std::vector<int> v(size, 0);
    std::vector< std::vector <int>> min(size - 1, std::vector<int>(size - 1, 0) );
    for ( int i = 0; i < size; i++ ) {
        get_minor(matrix, min, 0, i);
        calculate_minor(min, v[i]);
    }
    res = 0;
    for ( int i = 0; i < size; i++ ) {
        if ( i % 2 == 0 )
            res += v[i] * matrix[0][i];
        else
            res -= v[i] * matrix[0][i];
    }
}

void calculate_everything(const std::vector< std::vector <int>> &matrix, std::vector<int> &v, int start, int end) {
    int size  = matrix.size();
    std::vector< std::vector <int>> min(size - 1, std::vector<int>(size - 1, 0) );
    for (int i = start; i < end; i++ ) {
        get_minor(matrix, min, 0, i);
        calculate_minor(min, v[i]);
       // std::cout<<"minor is: "<<v[i]<<" "<<std::endl;
    }
}
void calculate_multi_thread(const std::vector< std::vector <int>> &matrix, int &res, int number) {
    int size = matrix.size();
    if (size == 1){
        res = matrix[0][0];
        return;
    }
    std::thread my_threads[number];
    std::vector<int> v(size, 0);
    for ( int i = 0; i < number - 1; i++ ) {
        int first = (i * size / number);
        int second = (i + 1) * (size / number);
        my_threads[i] = std::thread(calculate_everything, matrix, std::ref(v), first, second);
    }
    int left = (number - 1) * (size / number);
    my_threads[number - 1] = std::thread(calculate_everything, matrix, std::ref(v), left, size);
    for ( int i = 0; i < number; i++ ) {
        my_threads[i].join();
    }
    res = 0;
    for ( int i = 0; i < size; i++ ) {
        if ( i % 2 == 0 )
            res += v[i] * matrix[0][i];
        else
            res -= v[i] * matrix[0][i];
    }
}
