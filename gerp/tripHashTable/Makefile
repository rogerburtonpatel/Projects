#########################################################
#                   GERP: tripHashTable                 #
# by Roger Burtonpatel, 12/29/2021                      #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

THT: main.o tripHashTable.o
	${CXX} ${CXXFLAGS} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<
	
# remove executables and object code from the current folder 
clean: 
	rm tripHashTable.o main.o THT

