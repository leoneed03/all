#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
	void get_minor(std::vector< std::vector <int> > matrix, std::vector< std::vector <int> > &new_matrix, int k, int p);
	void print_matrix (std::vector< std::vector <int> > matrix);
    void calculate_multi_thread(std::vector< std::vector <int> > matrix, int &res);
    void calculate_one_thread(std::vector< std::vector <int> > matrix, int &res);
	void print();
void print_me();
#endif
