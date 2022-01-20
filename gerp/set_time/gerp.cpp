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
        // for (auto s : allLines) {
        //     std:: cout << s << std::endl;
        // }
        // the_table.printTable(std::cout);
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
        std::cout << "\nGoodbye! Thank you and have a nice day." << std::endl;
}

void gerp::read_all(std::string dirname)
{
    std::vector<std::string> filevector; 
    size_t index = 0;
    populateFileVector(dirname, filevector);

    for (std::string fname : filevector) {
        read_file(fname, index);
    }
}

void gerp::read_file(std::string filepath, size_t &index)
{    
    int linenumber = 1;
    std::string word; 
    std::string fullline;
    std::ifstream myfstream(filepath);
    if (myfstream.is_open()) {
        while (getline(myfstream, fullline)) {
              allLines.push_back(fullline);
              std::istringstream iss(fullline);
              while (iss >> word) {
                  the_table.insert(word, filepath, index, linenumber);
              }
        linenumber++;
        index++;
        }
        myfstream.close();
    }
    else {
        std::cerr << "Unable to open file " << filepath << "." << std::endl;
    }
}

void gerp::get(std::string Key, std::ofstream &output, bool insensitive)
{
    std::vector<wordPod> found_wps = the_table.get(Key, insensitive);

    // TODO CHANGE FOR INSENSITIVE ^^ 
    if (found_wps.empty()) {
        output << "query Not Found." 
               << (insensitive ? "" : " Try with @insensitive or @i.") 
               << std::endl;
    }

    for (auto wp : found_wps) {
        print(wp, output);
    }
}
void gerp::print(wordPod wp, std::ofstream &output)
{
    output << wp.filepath << ":" << wp.linenumber << " " << allLines[wp.v_index]
           << std::endl;
}
        
        // void get_queries();

