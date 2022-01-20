#include <iostream>
#include <fstream>
#include "gerp.h"
#include "tripHashTable.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "bad\n";
        exit(EXIT_FAILURE);
        //TODO FIX
    }

    std::ofstream outfile (argv[2]);
    if (outfile.is_open()) {
        gerp g;
        g.run(argv[1], outfile);
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file " << argv[2] << "." << std::endl;
    exit(EXIT_FAILURE);
    }
    return 0;
}