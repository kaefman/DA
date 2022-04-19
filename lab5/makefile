FLAGS= -std=c++17 -O2 -Wextra -Wall -Wno-sign-compare -Wno-unused-result -pedantic

all:solution
solution: main.o st.o
	g++ $(FLAGS) -o solution main.cpp st.cpp
benchmark: benchmark.o st.o
	g++ $(FLAGS) -o benchmark benchmark.cpp st.cpp
main.o: st.h
st.o: st.h
benchmark.o: st.h
clean: 
	rm -f *.o solution benchmark