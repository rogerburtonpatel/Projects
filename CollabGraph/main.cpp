/*
 * main.cpp
 * COMP 15 Project 2: Six Degrees of Collaboration
 * Driver for SixDegrees class. 
 * Simulates a graph of musical artists and their collaborations. Allows to see
 * paths between artists via collaborations using breadth-first or 
 * depth-first search, along with some other special commands. The graph
 * can also be printed. Exit by imputting "quit."
 * 
 * If you want to see a web of artist collabs and try to connect them using 
 * a text-based interface, this program may be useful to you. 
 * 
 * main.cpp handles file I/O and builds SixDegrees instances, running them 
 * based on number of inputs. 
 *
 * 
 * by Roger A. Burtonpatel, 4/20/2021
 */

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>

#include "SixDegrees.h"
using namespace std;

/* Helper functions that open files to shorten main function. */
ifstream read_infile(string filename);
ofstream read_outfile(string filename);

/* 
 * main(). 
 * Processes file I/O and executes an instance of SixDegrees, 
 * varying input based on number of input files given. 
 * 
 * Parameters: int num of command line arguments, the array of arguments
 * Returns:    0
 */
int main(int argc, char *argv[])
{
        if (argc < 2 or argc > 4) { // checks for correct number of files
            cerr << "Usage: ./SixDegrees dataFile [commandFile] [outputFile]"; 
            cerr << endl; 
            exit(EXIT_FAILURE); 
        }
            SixDegrees SD; // creates new SixDegrees using default constructor
        if (argc == 4) { // then open all files, run, and close them. 
            ofstream outputFStream = read_outfile(argv[3]);
            ifstream commandFStream = read_infile(argv[2]);
            ifstream artistStream = read_infile(argv[1]);
                SD.run(artistStream, commandFStream, outputFStream);
                outputFStream.close();
                commandFStream.close();
                artistStream.close();
        }
        else if (argc == 3) { // then open 2 files, run, and close them. 
            ifstream commandFStream = read_infile(argv[2]);
            ifstream artistStream = read_infile(argv[1]);
                SD.run(artistStream, commandFStream, cout);
                commandFStream.close();
                artistStream.close();
        }
        else { // then open artist file, run, and close it. 
            ifstream artistStream = read_infile(argv[1]);
                SD.run(artistStream, cin, cout);  
                artistStream.close();
        }
    return 0; 
}

/* 
 * read_infile()
 * Takes a string filename and attempts to open an ifstream using 
 * a file of that name. If opening fails, exits. Otherwise, 
 * returns the ifstream. 
 * 
 * Parameters: a string filename with which to open an ifstream
 * Returns:    an ifstream based on the opened file 
 */
ifstream read_infile(string filename) {
    ifstream if_stream(filename); 
    if (not if_stream.is_open()) { // checks 
            cerr << filename << " cannot be opened." << endl; 
            exit(EXIT_FAILURE);
    }
    return if_stream; // returns stream if it exists 
}

/* 
 * read_outfile()
 * Takes a string filename and attempts to open an ofstream using 
 * a file of that name. If opening fails, exits. Otherwise, 
 * returns the ofstream. 
 * 
 * Parameters: a string filename with which to open an ofstream
 * Returns:    an ofstream based on the opened file 
 */
ofstream read_outfile(string filename) {
    ofstream of_stream(filename); 
    if (not of_stream.is_open()) { // checks 
            cerr << filename << " cannot be opened." << endl; 
        exit(EXIT_FAILURE); 
    }
    return of_stream; // returns stream if it exists 
}
