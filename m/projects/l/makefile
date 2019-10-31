CXX = g++
CXXFLAGS = --std=c++11
LIBS = /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread
SRCS = m.cpp test.cpp
OBJS = $(SRCS:.cpp=.o)

matrices: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

valgrind_matrix_calc : $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -O0 -o $@

clean:
	@rm -f *.o
	@rm -f matrix_calc

#.PHONY: clean valgrind


