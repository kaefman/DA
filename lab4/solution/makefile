FLAGS = -std=c++17 -O2 -Wextra -Wall -Wno-sign-compare -Wno-unused-result -pedantic

all: main.o KMP.o
	g++ $(FLAGS) main.o KMP.o -o solution

main.o: main.cpp KMP.h
	g++ $(FLAGS) -c main.cpp

KMP.o: KMP.cpp KMP.h
	g++ $(FLAGS) -c KMP.cpp

clean:
	rm -f *.o solution