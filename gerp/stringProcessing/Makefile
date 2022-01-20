#########################################################
#                   GERP: stringProcessing              #
# by Roger Burtonpatel, 12/28/2021                      #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


FSTreeTraversal: stringProcessing.o 
	${CXX} ${CXXFLAGS} $^ -o stringProcessing

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<
	
# remove executables and object code from the current folder 
clean: 
	rm stringProcessing.o stringProcessing

