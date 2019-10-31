#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <set>
#include <iterator>
#include "array.h"

using namespace std;


safe_vector::safe_vector(std::vector<int> const &a): arr(a), m(vector<std::mutex>(a.size())){}

std::set<int> safe_vector::get_rand_ints(int n)
{
	std::set<int> s;
	while (s.size() < 3)
		s.insert(rand() % n);
	
	return s;
}

void safe_vector::count_sum()
{
	std::set<int> s = get_rand_ints(arr.size());
	auto s0 = s.begin();
	auto s1 = s.begin();
	auto s2 = s.begin();
	advance(s1, 1);
	advance(s2, 2);
		
	while (true)
	{
		if (!m[*s0].try_lock())
			continue;
		else
		{
			if (!m[*s1].try_lock())
			{
				m[*s0].unlock();
				continue;
			}
			else
			{
				if (!m[*s2].try_lock())
				{
					m[*s0].unlock();
					m[*s1].unlock();
					continue;
				}
				else
					break;
			}
		}
			
		
		
	}

		
	int summ = 0;
	//cout << "!!! "; 
	for (auto i = s.begin(); i != s.end(); i++)
	{
		summ += arr[*i];
		//cout << *i << " ";
	}
	//cout << endl;
		
		
	for (auto i = s.begin(); i != s.end(); i++)
		arr[*i] =  summ;
		
	//for (int i = 0; i < arr.size(); i++)
		//cout << arr[i] << ' ';
	//cout << endl << endl << endl <<endl; 
		
	for (auto i = s.begin(); i != s.end(); i++)
		m[*i].unlock();
		
	
	
}


void parse_threads(vector<int> const &a, int num_of_threads)
{

		std::thread threads[num_of_threads]; // for calculating minors
		//std::vector<int> a = {1, 2, 3, 4, 5};
		safe_vector sv(a);
		for (int i = 0; i < num_of_threads; i++)
		{
		   threads[i] = std::thread(&safe_vector::count_sum, &sv);
		}

		for (int i = 0; i < num_of_threads; i++)
		{
		    threads[i].join();
		}
			
}


