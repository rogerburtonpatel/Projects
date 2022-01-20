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
        // run will open the fstree into a temporary filenames vector
        void run        (std::string dirname, std::ofstream &output);

    private: 
        void read_all(std::string dirname);
        void get(const std::string &Key, std::ofstream &output, const bool &insensitive);
        void print(const wordPod &wp, std::ofstream &output);
        // passed by reference to increment index local to read_all()
        // throughout its lifetime 
        void read_file(const std::string &filepath, size_t &lineindex, 
                                                             size_t &fileindex);
        void get_queries(std::ofstream &output);

        std::vector<std::string> allLines;
        std::vector<std::string> filenames;
        tripHashTable the_table;
};

#endif