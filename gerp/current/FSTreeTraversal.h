#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H

/*
 * @Overview: 
 * FSTreeTraversal header. Reads in directory name and prints all accessible
 *      file names by traversing down the file tree from that directory. 
 *      Operates recursively (includes subdirectories)
 * 
 * @Purpose: Index a filetree into a list of string filenames. 
 * @Use: with another program that requires a a list of filenames based within
 *       a given filetree. 
 * 
 * @implementation-note: This implementation uses a vector to store the 
 *                       filenames.
 * 
 * @Author: rab
 * 
 * @chlog: 1/3/2022:  creation and initialization for modularity 
 *         1/18/2022: extensive documentation
 * 
 */

#include <iostream>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"


/* declarations -- see definitions for contracts */
void populateFileVector(std::string dirname, std::vector<std::string> &fileVec);
void treeTraversal(DirNode *d, bool rooted, std::vector<std::string> &fVec);


/*
 @name:     populateFileVector

 @args:     (-a string name of the directory at which file indexing shall begin,
             -a reference to a string vector which shall be populated)

 @purpose:  the function shall populate a string vector passed by reference 
            as the second argument with all files found within the filetree 
            rooted at the directory whose name is the first argument.

 @warnings: if the filetree contains a directory loop, the function may run 
            indefinitely. 
 */
void populateFileVector(std::string dirname, 
                                        std::vector<std::string> &fileVec) {
    FSTree filetree(dirname);

    treeTraversal(filetree.getRoot(), true, fileVec);
    
}

/*
 @name:     treeTraversal

 @args:     (-a pointer to a directory at which file indexing shall begin,
             -a boolean indicating if the first argument points to the root 
             directory, 
             -a reference to a string vector which shall be populated)

 @purpose:  the function shall populate a string vector passed by reference 
            as the third argument with all files found within the filetree 
            rooted at the directory pointed to by the first argument.

 @warnings: the function must be called with "true" as the second argument,
            or unexpected behavior shall occur; expected is 
            a segmentation fault.
 */

/* NOTE TO SELF: simple fix for trailing double // if reference changes: 
         check if getName() returns a string ending in / and 
         modify that string accordingly. Might even be readable
         in a ternary.  */
void treeTraversal(DirNode *d, bool rooted, 
                                            std::vector<std::string> &fVec) {
    /* set the name to name + parent */
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