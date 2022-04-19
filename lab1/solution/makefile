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

benchmark.o: benchmark.cpp pair.h sort.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: pair.h sort.h vector.h

clean:
	rm -f *.o $(EXECUTABLE) benchmark