#########################################################
#                   GERP: gerp                          #
# by Roger Burtonpatel, 1/3/2022                        #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


gerp: main.o gerp.o tripHashTable.o FSTree.o DirNode.o stringProcessing.o
	${CXX} ${CXXFLAGS} $^ -O2 -o gerp

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<
	
# remove executables and object code from the current folder 
clean: 
	rm tripHashTable.o main.o gerp.o stringProcessing.o gerp
