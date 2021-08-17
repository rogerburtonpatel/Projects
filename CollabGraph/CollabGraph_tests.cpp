/**
 **  CollabGraph_tests.cpp
 ** 
 ** COMP 15 project 2
 ** by Roger A. Burtonpatel, 4/21/2021
 ** 
 ** Uses Matt Russell's unit_test framework to test the CollabGraph.
 */
#include <cassert>
#include <vector>
#include <exception>

#include "CollabGraph.h"

/*
 * Tests the default graph construction. 
 * Parameters: none 
 * Returns:    none 
 */
void construct()
{
    CollabGraph();
}

/* 
 * Some early testing I did to get a sense of the Artist class and functions.
 * Makes sure Artist collaborations appear appropriately. 
 */
void collab_test()
{
    Artist A("A");
    Artist B("B");
    A.add_song("song1");
    B.add_song("song2");
    B.add_song("song1");
    assert(A.get_collaboration(B) == "song1");
}

/* 
 * Tests report_path() with manually-set predecessors. Uses 2 custom artists 
 * and manually inserts them into the graph with an edge. Checks functionality 
 * of report_path() by ensuring A (the source) is on top of the stack and that 
 * the stack size is 2. 
 * Parameters: none 
 * Returns:    none 
 */
void report_path_test()
{
    Artist A("A");
    Artist B("B");
    assert(A.get_name() == "A");
    A.add_song("song1");
    B.add_song("song2");
    B.add_song("song1");
    CollabGraph g;
    g.insert_vertex(A);
    g.insert_vertex(B);
    g.insert_edge(A, B, "song1");
    g.set_predecessor(B, A);
    assert(g.get_predecessor(B) == A);
    assert(g.report_path(A, B).top() == A);
    assert(g.report_path(A, B).size() == 2);
}

/* 
 * Tests report_path() with manually-set predecessors. Uses 2 custom artists 
 * and manually inserts them into the graph with no edge. Ensures resulting 
 * stack from report_path is empty
 * Parameters: none 
 * Returns:    none 
 */
void report_path_test_songless_artist()
{
    Artist A("A");
    Artist B("B");
    B.add_song("song2");
    B.add_song("song1");
    CollabGraph g;
    g.insert_vertex(A);
    g.insert_vertex(B);
    assert(g.report_path(A, B).size() == 0);
}


/*
 * Creates and returns a graph with a single vertex. Used to modularize 
 * later test code. 
 * 
 * Parameters: none 
 * Returns:    a graph with one vertex to be used later in testing for 
 * modularity. 
 */
CollabGraph make_graph_A()
{
    Artist A("A");
    A.add_song("song1");
    A.add_song("song4");
    CollabGraph g;
    g.insert_vertex(A);
    return g; 
}

/*
 * Creates and returns a graph with two vertices with a path between them.
 * One is a predecessor of the other. Used to modularize later test code. 
 * 
 * Parameters: none 
 * Returns:    a graph with two vertices to be used later in testing for 
 * modularity. 
 */
CollabGraph make_graph_AB_path()
{
    Artist A("A");
    Artist B("B");
    A.add_song("song1");
    B.add_song("song2");
    B.add_song("song1");
    CollabGraph g;
    g.insert_vertex(A);
    g.insert_vertex(B);
    g.insert_edge(A, B, "song1");
    g.set_predecessor(B, A);
    return g; 
}

/*
 * Creates and returns a graph with two vertices with no path between them.
 * Neither is a predecessor of the other. Used to modularize later test code.
 * 
 * Parameters: none 
 * Returns:    a graph with two vertices to be used later in testing for 
 * modularity. 
 */
CollabGraph make_graph_AB_no_path()
{
    Artist A("A");
    Artist B("B");
    A.add_song("song1");
    B.add_song("song2");
    CollabGraph g;
    g.insert_vertex(A);
    g.insert_vertex(B);
    return g; 
}

/*
 * Creates and returns a graph with four vertices with paths between them.
 * A predecessor loop exists within the graph (D->A->B->C->D).
 * Used to modularize later test code. 
 * 
 * Parameters: none 
 * Returns:    a graph with four vertices to be used later in testing for 
 * modularity. 
 */
CollabGraph make_graph_ABCD()
{
    Artist A("A");
    Artist B("B");
    Artist C("C");
    Artist D("D");
    A.add_song("song1");
    A.add_song("song4");
    B.add_song("song2");
    B.add_song("song1");
    C.add_song("song2");
    C.add_song("song3");
    D.add_song("song3");
    D.add_song("song4");
    CollabGraph g;
    g.insert_vertex(A);
    g.insert_vertex(B);
    g.insert_vertex(C);
    g.insert_vertex(D);
    g.insert_edge(A, B, "song1");
    g.insert_edge(B, C, "song2");
    g.insert_edge(C, D, "song3");
    g.insert_edge(D, A, "song4");    
    g.set_predecessor(B, A);
    g.set_predecessor(C, B);
    g.set_predecessor(D, C);
    g.set_predecessor(A, D);
    return g; 
}

/*
 * Tests report_path between vertices A and B (set as predecessors)
 * The vertices are predecessors of each other and should return a 
 * proper report_path stack of size 2. 
 *
 * 
 * Parameters: none 
 * Returns:    none 
 */ 
 
void report_path_test1()
{
    CollabGraph g =    make_graph_AB_path();
    std::stack<Artist> s = g.report_path(Artist("A"), Artist("B"));

    assert(s.top().get_name() == "A"); 
        s.pop();
    assert(s.top().get_name() == "B");
        s.pop();
    assert(s.empty());
}


/*
 * Tests report_path with a predecessor loop between A and D to ensure 
 * report_path() will stop at the correct time. report_path should 
 * return a proper stack of size 4. 
 * 
 * This test also ensures correct ordering of report_path with a 
 * larger sample size. 
 * 
 * Parameters: none 
 * Returns:    none 
 */
void report_path_test2()
{
    CollabGraph g =    make_graph_ABCD();
    std::stack<Artist> s = g.report_path(Artist("A"), Artist("D"));

    assert (s.size() == 4);

    assert(s.top().get_name() == "A"); 
        s.pop();
    assert(s.top().get_name() == "B");
        s.pop();
    assert(s.top().get_name() == "C");
        s.pop();
    assert(s.top().get_name() == "D");
        s.pop();
    assert(s.empty());
}

/*
 * Tests report_path between a vertex in the graph and a vertex 
 * not in the graph to ensure proper error-catching. 
 * 
 * Will try an error-causing block of code and catch the error with 
 * no output. 
 *  
 * Parameters: none 
 * Returns:    none 
 */
void report_path_test_not_in_graph()
{
    bool error_caught = false; // used to ensure error-catching 
    CollabGraph g =    make_graph_AB_path();
       try {
    std::stack<Artist> s = g.report_path(Artist("A"), Artist("D"));
       } // throws error since D is not in the graph 
     catch (std::runtime_error) {
         error_caught = true; // shows error was caught
    }
    assert(error_caught); // ensures error was caught 
}
/*
 * Tests that report_path() between two artists with no path between them 
 * (no predecessor connection) returns an empty stack. 
 * Parameters: none 
 * Returns:    none 
 */
void report_path_test_no_path()
{
    CollabGraph g =    make_graph_AB_no_path();
    std::stack<Artist> s = g.report_path(Artist("A"), Artist("B"));
    assert(s.empty());
}


/*
 * Tests get_vertex_neighbors() with a 2-artist graph for Artist A.
 * Ensures the vector returned contains only A's single neighbor. 
 * Parameters: none 
 * Returns:    none 
 */
void get_vertex_neighbors_test1()
{
    CollabGraph g = make_graph_AB_path();
    std::vector<Artist> v = g.get_vertex_neighbors(Artist("A"));
    assert(v[0].get_name() == "B");
    assert(v.size() == 1);
}

/*
 * Tests get_vertex_neighbors() with a 4-artist graph for Artist B
 * Ensures the vector returned contains only B's two neighbors. 
 * Parameters: none 
 * Returns:    none 
 */
void get_vertex_neighbors_test2()
{
    CollabGraph g = make_graph_ABCD();
    std::vector<Artist> v = g.get_vertex_neighbors(Artist("B"));
    assert(v[0].get_name() == "A");
    assert(v[1].get_name() == "C");
    assert(v.size() == 2);
}

/*
 * Test to ensure get_vertex_neighbors() on a vertex with no neighbors
 * returns an empty vector. 
 * Parameters: none 
 * Returns:    none 
 */
void get_vertex_neighbors_test_single_vertex()
{
    CollabGraph g = make_graph_A();
    std::vector<Artist> v = g.get_vertex_neighbors(Artist("A"));
    assert(v.size() == 0);
}


/*
 * Tests report_path between a vertex in the graph and a vertex 
 * not in the graph to ensure proper error-catching. 
 * 
 * Will try an error-causing block of code and catch the error with 
 * no output. 
 *  
 * Parameters: none 
 * Returns:    none 
 */
void get_vertex_neighbors_test_not_in_graph()
{
    bool error_caught = false; // used to ensure error-catching 
    CollabGraph g =    make_graph_AB_path();
       try {
    std::vector<Artist> v = g.get_vertex_neighbors(Artist("D"));
       } // throws error since D is not in the graph 
     catch (std::runtime_error) {
         error_caught = true; // shows error was caught
    }
    assert(error_caught); // ensures error was caught 
}
