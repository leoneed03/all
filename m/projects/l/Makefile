CXX = g++
CXXFLAGS = —std=c++17
LIBS = /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread
SRCS = $(wildcard *.cpp)
OBJS = $(filter %.o,$(SRCS:.cpp=.o) $(SRCS:.cc=.o))

matrix_calc: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

valgrind_matrix_calc : $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -O0 -o $@

clean:
	@rm -f *.o
	@rm -f matrix_calc

#.PHONY: clean valgrind


