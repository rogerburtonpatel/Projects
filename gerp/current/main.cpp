#include <iostream>
#include <fstream>
#include "gerp.h"
#include "tripHashTable.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }

    std::ofstream outfile (argv[2]);
    if (outfile.is_open()) {
        gerp g;
        g.run(argv[1], outfile);
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file " << argv[2] << ".\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}