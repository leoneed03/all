#pragma once

#ifndef ARRAY_H
#define ARRAY_H

#include <mutex>

class safe_vector
{
	private:
		std::vector<int> arr;
		std::vector<std::mutex> m;
		
		std::set<int> get_rand_ints(int n);

	public:
		safe_vector(std::vector<int> const &a);
		void count_sum();
		
};


void parse_threads(std::vector<int> const &a, int num_of_threads);


#endif
