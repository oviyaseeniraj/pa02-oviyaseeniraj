#MAKEFILE

CXXFLAGS: -std=c++11 -g -Wall -Wno -uninitialized

all: runMovies
		./runMovies

runMovies: main.cpp movies.cpp
		g++ $(CXXFLAGS) main.cpp movies.cpp -o runMovies

clean:
		rm runMovies
