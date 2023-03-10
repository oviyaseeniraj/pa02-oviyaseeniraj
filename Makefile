# MAKEFILE

# CXXFLAGS: -std=c++11 -g -Wall -Wno -uninitialized

# all: runMovies
# 		./runMovies

# runMovies: main.cpp movies.cpp
# 		g++ $(CXXFLAGS) main.cpp movies.cpp -o runMovies

# clean:
# 		rm runMovies

CXX = g++

CXXFLAGS= -Wall -Wno-uninitialized #-DWITHOUT_NUMPY -I/usr/local/include/python3.10 -lpython3.10


OBJECTFILES = main.o movies.o
TARGET = runMovies

all: ${TARGET}

${TARGET}: ${OBJECTFILES}
	$(CXX) ${CXXFLAGS} -o ${TARGET} ${OBJECTFILES} 

clean:
	/bin/rm -f ${TARGET} *.o