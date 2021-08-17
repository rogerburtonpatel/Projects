/**
 ** SixDegrees.cpp
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Purpose:
 **   Represent a collaboration graph of artists, where each artist is
 **   a vertex and an edge between two artists is a song in which those
 **   artists have collaborated. Accessor and mutator functions are provided,
 **   allowing for convenient traversal of the graph.
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
 ** 19 April - 2 May rburto03
 **
 **/

#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue> 

#include "SixDegrees.h"

using namespace std; 

/* 
 * Default constructor for SixDegrees
 * 
 * Initializes a new instance of SixDegrees. 
 * 
 * Parameters: none 
 * Returns:    none 
 */ 
SixDegrees::SixDegrees()
{

}

/* 
 * Default destructor for SixDegrees
 * 
 * Destroys the SixDegrees, recycling all memory used.  
 * 
 * Parameters: none 
 * Returns:    none 
 */ 
SixDegrees::~SixDegrees()
{

}


/* 
 * run/execution function for SixDegrees
 * 
 * Runs the program by. Creates the interactive user interface 
 * using the given input files and gets commands from the user. 
 * 
 * Parameters: an ifstream artistStream, an istream (could be 
 * cin or stream from command file, an ostream (could be cout or 
 * stream from output file.))
 * Returns:    none 
 */ 
void SixDegrees::run(ifstream& artistStream, istream& inputStream,
                                                ostream& outStream)
{

    make_artists(artistStream); // builds artist graph based on input
       get_input(inputStream, outStream); // gets commands 
                                            // from cin or commandStream
}

/* 
 * Graph-creation function for SixDegrees
 * 
 * Initializes a graph of artists based on the given artists file. 
 * Reads artist name and song list until "*" is read. 
 * 
 * Parameters: none 
 * Returns:    none 
 */ 
void SixDegrees::make_artists(ifstream &artistStream)
{
    vector<Artist> artists; 
    string artistName, songName; 
    string STOP = "*"; 

    while (getline(artistStream, artistName)) {
        Artist artist(artistName); // Writes over a new artist
        getline(artistStream, songName); // starts getting song names
        while (songName != STOP) {
                         // adds them until * is reached
            artist.add_song(songName);
            getline(artistStream, songName);
        }
        artists.push_back(artist);
    }
    for (size_t i = 0; i < artists.size(); ++i) {
        the_graph.insert_vertex(artists[i]);
    }
    for (size_t i = 0; i < artists.size(); ++i) {
        for (size_t j = 0; j < artists.size(); ++j) {
            if (artists[i].get_collaboration(artists[j]) != "" and i != j) {
                the_graph.insert_edge(artists[i], artists[j], 
                (artists[i].get_collaboration(artists[j])));
            }
        }
    }
}

/* 
 * Breadth-first search helper function for SixDegrees
 * 
 * Reads in 2 artist names on which to perform a breadth-first search 
 * to find a collaboration path. Prints an error if one or 
 * more artists are not found in the graph. 
 * 
 * Parameters: an input stream from which to read the artists, 
 * an output stream to which to print error messages. 
 * Returns:    none 
 */ 
void SixDegrees::bfs(istream& inputStream, ostream& outStream)
{
    string name1, name2;
    
    getline(inputStream, name1);
    getline(inputStream, name2);
    
    Artist source(name1);
    Artist dest(name2);

    if (not the_graph.is_vertex(source)) 
        outStream << "\"" << source << "\" was not found in the dataset :(\n";
    if (not the_graph.is_vertex(dest)) 
        outStream << "\"" << dest << "\" was not found in the dataset :(\n";

    if (the_graph.is_vertex(source) and the_graph.is_vertex(dest)) 
        print_path(bfs(source, dest, outStream), outStream);
}

/* 
 * Breadth-first search function for SixDegrees
 * 
 * Performs a breadth-first search 
 * on two given artists to find a collaboration path. 
 * Prints an message if no path is found, or returns path to be 
 * printed. 
 * 
 * Parameters: a source and destination artist from which to build the pathway,
 * an output stream to which to print no-path messages. 
 * Returns:    a stack representing the pathway to be printed. 
 */ 
stack<Artist> SixDegrees::bfs(Artist &source, Artist &dest, 
                                     ostream& outStream)
{
    stack<Artist> s; // later set to report path or returned empty 
        the_graph.clear_metadata(); 
        queue<Artist> neighbors;
        neighbors.push(source);
        while (not neighbors.empty()) { //bfs algorithm; sets predecessors 
            Artist first = neighbors.front();
            neighbors.pop();
            the_graph.mark_vertex(first);     
            for (Artist n : the_graph.get_vertex_neighbors(first)) {
                if (not the_graph.is_marked(n)) {
                    the_graph.mark_vertex(n);
                    the_graph.set_predecessor(n, first);
                    neighbors.push(n);
                }
            }
        }   
    s = the_graph.report_path(source, dest); // sets report path if exists 
    
    if (s.empty()) 
        print_no_path(source, dest, outStream); // prints that no path exists
    return s; // returns report path 
}

/* 
 * Depth-first search helper function for SixDegrees
 * 
 * Reads in 2 artist names on which to perform a depth-first search 
 * to find a collaboration path. Prints an error if one or 
 * more artists are not found in the graph. 
 * 
 * Parameters: an input stream from which to read the artists, 
 * an output stream to which to print error messages. 
 * Returns:    none 
 */ 
void SixDegrees::dfs(istream& inputStream, ostream& outStream)
{
    string name1, name2;
    
    getline(inputStream, name1);
    getline(inputStream, name2);
    
    Artist source(name1);
    Artist dest(name2);

    if (not the_graph.is_vertex(source)) 
        outStream << "\"" << source << "\" was not found in the dataset :(\n";
    if (not the_graph.is_vertex(dest)) 
        outStream << "\"" << dest << "\" was not found in the dataset :(\n";

    if (the_graph.is_vertex(source) and the_graph.is_vertex(dest)) 
        print_path(dfs(source, dest, outStream), outStream);
}

/* 
 * Depth-first search function for SixDegrees
 * 
 * Performs a Depth-first search 
 * on two given artists to find a collaboration path. 
 * Prints an message if no path is found, or returns path to be 
 * printed. 
 * 
 * Parameters: a source and destination artist from which to build the pathway,
 * an output stream to which to print no-path messages. 
 * Returns:    a stack representing the pathway to be printed. 
 */ 
stack<Artist> SixDegrees::dfs(Artist &source, Artist &dest, 
                                     ostream& outStream)
{
    stack<Artist> s; // later set to report path or returned empty 
        the_graph.clear_metadata(); 
        stack<Artist> neighbors; 
        neighbors.push(source);
        while (not neighbors.empty()) { //dfs algorithm; sets predecessors 
            Artist first = neighbors.top();
            neighbors.pop();
            the_graph.mark_vertex(first);     
            for (Artist n : the_graph.get_vertex_neighbors(first)) {
                if (not the_graph.is_marked(n)) {
                    the_graph.mark_vertex(n);
                    the_graph.set_predecessor(n, first);
                    neighbors.push(n);
                }
            }
        }   
    s = the_graph.report_path(source, dest); // sets report path if exists 
    
    if (s.empty()) 
        print_no_path(source, dest, outStream); // prints that no path exists
    return s; // returns report path 
}

/* 
 * Exclusive search helper function for SixDegrees
 * 
 * Reads in 2 artist names on which to perform an exclusive search 
 * to find a collaboration path. Prints an error if one or 
 * more artists are not found in the graph. 
 * 
 * Parameters: an input stream from which to read the artists, 
 * an output stream to which to print error messages. 
 * Returns:    none 
 */ 
void SixDegrees::NOT(istream& inputStream, ostream& outStream)
{
    string name1, name2, input;
    
    getline(inputStream, name1);
    getline(inputStream, name2);

    vector<Artist> without; 
    string STOP = "*";

    getline(inputStream, input);

    while (input != STOP and not inputStream.eof()) {
        Artist a(input);
        if (the_graph.is_vertex(a))
            without.push_back(a);
        else
            outStream << "\"" << a << "\" was not found in the dataset :(\n";
        getline(inputStream, input);
    }
    
    Artist source(name1);
    Artist dest(name2);
    if (not the_graph.is_vertex(source)) 
        outStream << "\"" << source << "\" was not found in the dataset :(\n";
    if (not the_graph.is_vertex(dest)) 
        outStream << "\"" << dest << "\" was not found in the dataset :(\n";
        
    if (the_graph.is_vertex(source) and the_graph.is_vertex(dest))
        print_path(NOT(source, dest, without, outStream), outStream);
}

/* 
 * Exclusive search function for SixDegrees
 * 
 * Performs an exclusive search (search for a path between two artists 
 * using breadth-first serach that excludes a user-inputted subset of artists)
 * on two given artists to find a collaboration path. 
 * Prints an message if no path is found, or returns path to be 
 * printed. 
 * 
 * Parameters: a source and destination artist from which to build the pathway,
 * a vector of Artists to exclude from the search algorithm,
 * an output stream to which to print no-path messages. 
 * Returns:    a stack representing the pathway to be printed. 
 */ 
stack<Artist> SixDegrees::NOT(Artist &source, Artist &dest,
                                vector<Artist> without, 
                                     ostream& outStream)
{
    stack<Artist> s; // later set to report path or returned empty 
     
        the_graph.clear_metadata(); 
        queue<Artist> neighbors;
        neighbors.push(source);
        while (not neighbors.empty()) { //bfs algorithm; sets predecessors 
            Artist first = neighbors.front();
            neighbors.pop();
            the_graph.mark_vertex(first);     
            for (Artist n : the_graph.get_vertex_neighbors(first)) {
                if (not the_graph.is_marked(n)
                    and not any_of(without.begin(), without.end(), 
                    [&](const Artist &a) 
                    { return a == n or a == source; } )) { 
    // small Lambda which seemed simple as a solution - see README
                    the_graph.mark_vertex(n); 
                    the_graph.set_predecessor(n, first);
                    neighbors.push(n);
                }
            }
        }   
    s = the_graph.report_path(source, dest); // sets report path if exists 
    
    if (s.empty()) 
        print_no_path(source, dest, outStream); // prints that no path exists
    return s; // returns report path 
}

/*  
 * path-printer function 
 * 
 * prints the full path between given by a search algorithm. 
 * 
 * Parameters: a stack (path between artists), and an outStream
 * to print the path to.  
 * Returns:    none 
 */ 
void SixDegrees::print_path(stack<Artist> s, ostream& outStream) {

    if (not s.empty()) {
        Artist first, second;
        first = s.top();
        s.pop();
        second = s.top(); 
        s.pop();
        print_collab(first, second, outStream);

        while (not s.empty()) {
            first = second;
            second = s.top();
            s.pop();
            print_collab(first, second, outStream);
        }
        outStream << "***" << endl;   
    }
}

/*  
 * no-path-printer helper function 
 * 
 * prints that no path exists between two given artists. Called
 * if no path between them exists. 
 * 
 * Parameters: two artists to be printed to a no-path statement, 
 * an outStream to print it to. 
 * Returns:    none 
 */ 
void SixDegrees::print_no_path(Artist &source, Artist &dest,
                                        ostream& outStream) {

    outStream << "A path does not exist between "
        << "\"" << source << "\"" << " and " 
        << "\"" << dest << "\"" << 
        "." << endl;
}

/*  
 * collab-printer helper function 
 * 
 * prints a collab between Artists "first" and "second"
 * to the given outStream. 
 * 
 * Parameters: two artists to be printed together as a collab, 
 * an outStream to print them to. 
 * Returns:    none 
 */ 

void SixDegrees::print_collab(Artist &first, Artist &second,
                                        ostream& outStream) {
    outStream << "\"" << first << "\" collaborated with " 
    << "\"" << second << "\" in " 
    << "\"" << the_graph.get_edge(first, second) << "\"." << endl;
}


/*  
 * Input-getter function for SixDegrees
 * 
 * gets input from the user. Ends if user inputs "quit" or if 
 * commands end. 
 * 
 * Parameters: an input stream (cin or the command file stream),
 * an ostream (cout or the output file stream)
 * Returns:    none 
 */ 
void SixDegrees::get_input(std::istream &inputStream, ostream &outStream)
{
    string input; 
    while (not program_over and getline(inputStream, input)) { 
                                 // instead of reading directly from the 
                                 // stream using >> so as to follow 
                                 // reference format 
    if (input == "print")
        the_graph.print_graph(outStream);

    else if (input == "bfs") 
        bfs(inputStream, outStream);
    else if (input == "dfs") 
        dfs(inputStream, outStream);
    else if (input == "not")
        NOT(inputStream, outStream);

    else if (input == "quit") 
        program_over = true; // ends the program 
    
    else 
        outStream << input << " is not a command. Please try again.\n";

    }
}
