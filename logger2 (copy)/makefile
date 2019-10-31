CC = g++
CMP = --std=c++11
LIBS = -pthread -lgtest
SRC = logger.cpp task.cpp 
OBJS = $(SRC:.cpp=.o)

logger: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

%.o: %.cc
	$(CC) $(CMP) -c -g $< -O0 -o $@

clean:
	rm -rf *.o
	rm -rf logger


