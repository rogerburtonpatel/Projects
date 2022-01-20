#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H

/*
 * @Overview: 
 * FSTreeTraversal header. Reads in directory name and prints all accessible
 *      file names by traversing down the file tree from that directory. 
 *      Operates recursively (includes subdirectories)
 * 
 * @Purpose: Demonstration and testing of FSTree and DirNode classes 
 * @Use: with other files TODO ADD 
 * 
 * @Author: Roger A. Burtonpatel 
 * 
 * @chlog: 1/3-- creation and initialization for modularity 
 * 
 *
 * 
 */

#include <iostream>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"


// declarations 
void populateFileVector(const std::string &dirname, std::vector<std::string> &fileVec);
void treeTraversal(DirNode *d, const bool &rooted, std::vector<std::string> &fVec);


// this function will be used in other files-- namely, main.cpp (root)
// to do this, we'll comment out the main here and compile into a .o with the 
// main Makefile. From there, we'll compile that .o with DirNode.o and FSTree.o
// with everything else. 
void populateFileVector(const std::string &dirname, 
                                        std::vector<std::string> &fileVec) {
    FSTree filetree(dirname);

    treeTraversal(filetree.getRoot(), true, fileVec);
    
}

void treeTraversal(DirNode *d, const bool &rooted, 
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

#endif