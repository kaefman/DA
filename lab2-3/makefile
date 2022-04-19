CC=g++
CFLAGS=-std=c++17 -pedantic -Wall -Wextra -Wno-unused-variable
EXECUTABLE=solution
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

benchmark: benchmark.o 
	$(CC) $(FLAGS) benchmark.o -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

benchmark.o: benchmark.cpp node.h tree.h main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

main.o: node.h tree.h main.cpp

clean:
	rm -f *.o $(EXECUTABLE) benchmark