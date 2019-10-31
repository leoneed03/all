#include <valgrind/drd.h>
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(addr) ANNOTATE_HAPPENS_BEFORE(addr)
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(addr)  ANNOTATE_HAPPENS_AFTER(addr)

//#include "determinant.cpp"
#include <gtest/gtest.h>
#include <functional>
#include "array.hpp"
#include <ctime>


using namespace std;

TEST(TestSum, Test1)
{
	
    vector<int> a = {1, 2, 3, 4, 5};

	int num_of_threads = 10;
	
    parse_threads(ref(a), num_of_threads);

}

TEST(TestSum, Test2)
{
	
    vector<int> a(100);
    
    for (int i = 0; i < 100; i++)
    {
    	a[i] = 1;
    }

	int num_of_threads = 4;
	
    parse_threads(ref(a), num_of_threads);

}

TEST(TestSum, Test3)
{
	
    vector<int> a(7);
    
    for (int i = 0; i < 7; i++)
    {
    	a[i] = 1;
    }

	int num_of_threads = 6;
	
    parse_threads(ref(a), num_of_threads);

}





int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}
