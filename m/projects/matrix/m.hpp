#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
    void calculate_minor( const std::vector< std::vector <int>>& matrix, int &res );
    void get_minor(const std::vector< std::vector <int>> &matrix, std::vector<  std::vector <int>> &new_matrix, int k, int p);
    void print_matrix (const std::vector< std::vector <int>> &matrix);
    void calculate_multi_thread(const std::vector< std::vector <int>> &matrix, int &res);
    void calculate_one_thread(const std::vector< std::vector <int>> &matrix, int &res);
	void calculate_everything(const std::vector< std::vector <int>> &matrix, int &res, int k) ;

#endif
