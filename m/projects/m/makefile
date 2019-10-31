CC = g++
CMP = --std=c++11
LIBS = -pthread -lgtest
SRC = m.cpp test.cpp
OBJS = $(SRC:.cpp=.o)

matrices: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

%.o: %.cc
	$(CC) $(CMP) -c -g $< -O0 -o $@

clean:
	rm -rf *.o
	rm -rf matrices


