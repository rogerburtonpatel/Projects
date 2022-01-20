#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "tripHashTable.h"
#include "stringProcessing.h"
#include "wordPod.h"
#include "gerp.h"
#include "FSTreeTraversal.h"

void gerp::run(std::string dirname, std::ofstream &output)
{
        read_all(dirname);
        get_queries(output);
}

void gerp::read_all(std::string dirname)
{
    size_t lineindex = 0;
    size_t fileindex = 0;

    populateFileVector(dirname, filenames);

    for (std::string fname : filenames) {
        read_file(fname, lineindex, fileindex);
    }
}

void gerp::read_file(std::string filepath, size_t &lineindex, size_t &fileindex)
{    
    size_t linenumber = 1;
    std::string word; 
    std::string fullline;
    std::ifstream myfstream(filepath);
    if (myfstream.is_open()) {
        while (getline(myfstream, fullline)) {
              allLines.push_back(fullline);
              std::istringstream iss(fullline);
              while (iss >> word) {
                  the_table.insert(word, fileindex, lineindex, linenumber);
              }
        linenumber++; // this is reset to 1 with every new file 
        lineindex++;      // this is not. 
        }
        myfstream.close();
    }
    else {
        std::cerr << "Unable to open file " << filepath << ".\n";
    }
        fileindex++;  // neither is this. 
}

void gerp::get(std::string Key, std::ofstream &output, bool insensitive)
{
    std::vector<wordPod> found_wps = the_table.get(Key, insensitive);

    if (found_wps.empty()) {
        output << Key << " Not Found." 
               << (insensitive ? "" : " Try with @insensitive or @i.")
               << "\n";
    }
    for (auto wp : found_wps) {
        print(wp, output);
    }
}
void gerp::print(wordPod wp, std::ofstream &output)
{
    output << filenames[wp.fileindex] << ":" << wp.linenumber << ": " 
           << allLines[wp.lineindex]
           << "\n";
}
        
void gerp::get_queries(std::ofstream &output)
{
    stringProcessing sp;

    std::string input = "";
    std::cout << "Query? ";
    while (std::cin >> input and input != "@q" and input != "@quit") {
        if (input == "@i" or input == "@insensitive") {
            std::cin >> input;
            get(sp.stripNonAlphaNum(input), output, true);
        }
        else if (input == "@f") {
            std::cin >> input;
            output.close();
            output.open(input);
        }
        else if (input != "@q") {
            get(sp.stripNonAlphaNum(input), output, false);
        }
        std::cout << "\nQuery? ";
    }
    std::cout << "\nGoodbye! Thank you and have a nice day.\n";
}
