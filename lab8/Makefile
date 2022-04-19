CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp QSort.cpp
OBJ = $(FILES:.cpp=.o)
NAME = solution

all: solution

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.cpp: QSort.hpp
QSort.cpp: QSort.hpp

clean:
	rm -f *.o $(NAME)