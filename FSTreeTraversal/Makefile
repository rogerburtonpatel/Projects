#########################################################
#                   GERP: FSTreeTraversal               #
# by Roger Burtonpatel, 12/28/2021                      #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o 
	${CXX} ${CXXFLAGS} $^ -o treeTraversal

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<
	
# remove executables and object code from the current folder 
clean: 
	rm FSTreeTraversal.o treeTraversal
