#ifndef GERP_H
#define GERP_H

#include <iostream>
#include <vector>
#include <string>
#include "tripHashTable.h"
#include "stringProcessing.h"
#include "wordPod.h"


class gerp {
    public: 
        void get     (std::string Key, std::ofstream &output, 
                                                             bool insensitive);
        void print(wordPod wp, std::ofstream &output);
        // run will open the fstree into a temporary filenames vector
        void run        (std::string dirname, std::ofstream &output);
        
        void    read_all(std::string dirname);
        // passed by reference to increment index local to read_all()
        // throughout its lifetime 
        void    read_file(std::string filepath, size_t &index);
        
        void get_queries();
    private: 
        std::vector<std::string> allLines;
        tripHashTable the_table;
};

#endif