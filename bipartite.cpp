/**
    Recognizing Bipartite Graphs
    @file bipartite.cpp
    @author Gideon Kobea
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Graph.h"

using namespace std;

/**
 * Helper function to read a single edge from a line
 *
 * @param instream the input stream to read from
 * @param graph the graph to add the edge to
 */
void read_edge(istream & instream, Graph & graph) {
    string line;
    getline(instream, line);
    istringstream ss(line);
    size_t vertex = std::numeric_limits<size_t>::max();
    size_t neighbor = std::numeric_limits<size_t>::max();
    ss >> vertex >> neighbor;
    graph.add_edge(vertex, neighbor);
}

/**
 * Helper function to read a graph from the given file
 *
 * @param file_name the name of the file to read
 * @return the graph that was read
 */
Graph read_graph(const string & file_name) {
    ifstream instream(file_name);

    if(!instream.is_open()){
        cout << "File not found: " << file_name << endl;
    throw invalid_argument("File not found: " + file_name);
    }

    size_t num_vertices = 0, num_edges = 0, sum_of_degrees = 0;

    instream >> num_vertices;
    instream >> num_edges;
    sum_of_degrees = 2 * num_edges;

    Graph my_graph(num_vertices);

    instream.get(); // get end of line char

    size_t lines_read = 0;
    while (lines_read < sum_of_degrees and instream.good() and !instream.eof()) {
        read_edge(instream, my_graph);
        lines_read++;
    }

    return my_graph;
}

/**
 * main driver of the program. Read a graph and detect if bipartite
 *
 * @param argc the number of command-line arguments
 * @param argv an array of argument c-strings
 * @return an error code
 */
int main(int argc, char ** argv) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << " <file name>" << endl;
        exit(1);
    }

    const string file_name = argv[1];

    Graph graph = read_graph(file_name);
    bool bipartite = graph.is_bipartite();
    vector<Color> node_colors = graph.get_colors();

    cout << "The graph " << (bipartite ? "is" : "is not") << " bipartite" << endl;

    // Set to false if you don't want to see the color of each node.
    bool print_node_colors = true;
    if(print_node_colors){
        cout << "Node colors: ";
        size_t i;
        for(i = 0; i < node_colors.size() - 1; i++){
            Color c = node_colors[i];
            cout << c << ", ";
        }
        cout << node_colors[i] << endl;
    }

    return 0;
}
