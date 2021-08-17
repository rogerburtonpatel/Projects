/**
 ** SixDegrees.h
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Purpose:
 **   Represent an interactive interface between the user and a collaboration 
 **   graph of artists, where each artist is a vertex and an edge between two
 **   artists is a song in which those artists have collaborated. As of 
 **   4/21/2021, allows for initialization of the graph with an input file, 
 **   a commands file, and an output file, as well as printing and quitting. 
 **
 ** Notes:
 **   0) Artists with the empty string as their name are forbidden 
 **   1) The program stops when reaching the end of a commands file, if 
 **   provided, or when "quit" is inputted. 
 **
 ** ChangeLog:
 ** 18 April 2021 rburto03
 **
 **/

#ifndef __SIX_DEGREES_H__
#define __SIX_DEGREES_H__

#include "CollabGraph.h"

class SixDegrees {

public: 

    /* Default constructor */
    SixDegrees();

    /* Destructor */
    ~SixDegrees();

     /* Program running function */ 
    void run(std::ifstream& artistStream, std::istream& inputStream, 
                                        std::ostream& outStream);

    /* Public wrapper functions for bfs, dfs, not */
    void bfs(std::istream& inputStream, std::ostream& outStream); 
    void dfs(std::istream& inputStream, std::ostream& outStream); 
    void NOT(std::istream& inputStream, std::ostream& outStream); 

private: 

    /* Graph construction */
    void make_artists(std::ifstream &artistStream);

    /* BFS, DFS, and "not" private methods */ 
    std::stack<Artist> bfs(Artist &source, Artist &dest, 
                               std::ostream& outStream);
    std::stack<Artist> dfs(Artist &source, Artist &dest, 
                               std::ostream& outStream);
    std::stack<Artist> NOT(Artist &source, Artist &dest,
                            std::vector<Artist> without, 
                               std::ostream& outStream);

    void print_path(std::stack<Artist> s, std::ostream& outStream);

    void print_no_path(Artist &source, Artist &dest, std::ostream& outStream);

    void print_collab(Artist &source, Artist &dest, std::ostream& outStream);


    /* flag to end the program */
    bool program_over = false; 
    
    /* input-reader function, whether from cin or a commands file */
    void get_input(std::istream &inputStream, 
                            std::ostream &outStream);
    
    /* the graph itself */
    CollabGraph the_graph;
    
};
#endif /* __SIX_DEGREES_H__ */
