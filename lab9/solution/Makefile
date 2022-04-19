CC=g++
CFLAGS=-std=c++17 -pedantic -Ofast -O2
EXECUTABLE=solution
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
