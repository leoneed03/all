#ifndef _U_
#define _U_

#include <iostream>
#include <vector>
#include <thread>
#include "m.hpp"

void get_minor(std::vector<std::vector <int>> &matrix, std::vector<std::vector <int>> &new_matrix, int k, int p) {
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

void print_matrix (std::vector<std::vector <int>> matrix) {
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix [i][j] << "\t " ;
        }
        std::cout << std::endl;
    }
}
void calculate_multi_thread(std::vector< std::vector <int>> matrix, int &res) {
    int size = matrix.size();
    if (size == 1){
        res = matrix[0][0];
        return;
    }
    std::thread my_threads[size];
    std::vector<int> v(size, 0);
    std::vector<std::vector <int>> min(size - 1, std::vector<int>(size - 1, 0) );
 
    for ( int i = 0; i < size; i++ ) {
        get_minor(matrix, min, 0, i);
        my_threads[i] = std::thread ( calculate_multi_thread, min, std::ref(v[i]));
    }
    for ( int i = 0; i < size; i++ ) {
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
#endif
