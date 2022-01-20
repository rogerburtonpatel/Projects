/*
 * @Overview: 
 * FSTreeTraversal driver. Reads in directory name and prints all accessible
 *      file names by traversing down the file tree from that directory. 
 *      Operates recursively (includes subdirectories)
 * 
 * @Purpose: Demonstration and testing of FSTree and DirNode classes 
 * @Use: compile with "make" and run with ./treeTraversal dirname
 * 
 * @Author: Roger A. Burtonpatel 
 * 
 * @chlog: 12/28-- creation and initialization 
 * 
 *
 * 
 */

#include <iostream>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"

void populateFileVector(std::string dirname, std::vector<std::string> &fileVec);
void treeTraversal(DirNode *d, bool rooted, std::vector<std::string> &fVec);

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: ./treeTraversal Directory" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::vector<std::string> filevector; 
    populateFileVector(argv[1], filevector);

    for (auto filename : filevector) {
        std::cout << filename << std::endl;
    }

    return 0;
}

// this function will be used in other files-- namely, main.cpp (root)
// to do this, we'll comment out the main here and compile into a .o with the 
// main Makefile. From there, we'll compile that .o with DirNode.o and FSTree.o
// with everything else. 
void populateFileVector(std::string dirname, 
                                        std::vector<std::string> &fileVec) {
    FSTree filetree(dirname);

    treeTraversal(filetree.getRoot(), true, fileVec);
    
}

void treeTraversal(DirNode *d, bool rooted, 
                                            std::vector<std::string> &fVec) {
    // set the name to name + parent
    if (not rooted) {
        d->setName(d->getParent()->getName() + "/" + d->getName());
    }

    for (int i = 0; i < d->numFiles(); ++i) {
        fVec.push_back(d->getName() + "/" + d->getFile(i));
    }

    for (int i = 0; i < d->numSubDirs(); ++i) {
        treeTraversal(d->getSubDir(i), false, fVec);
    }
}