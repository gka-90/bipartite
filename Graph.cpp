/**
    Recognizing Bipartite Graphs
    @file Graph.cpp
    @authors Gideon Kobea
    @citation: https://www.youtube.com/watch?v=-vu34sct1g8
*/
#include <iostream>
#include <vector>
#include <list>
#include "Graph.h"

using namespace std;

/**
 * Makes nice printing of enum Color
 */
std::ostream& operator<<(std::ostream& o, Color c)
{
    static vector<string> enumNames = {"WHITE", "BLUE", "RED"};
    o << enumNames[static_cast<int>(c)];
    return o;
}

/**
 * Constructor, initialize graph with a given numbe of vertices
 *
 * @param num_vertices the number of vertices in the graph
 */
Graph::Graph(const size_t num_vertices) {
    _adj_list.resize(num_vertices);
    _colors.resize(num_vertices, WHITE);
}

/**
 * add the given edge to the graph
 *
 * @param u the first vertex of the edge
 * @param v the second vertex of the edge
 */
void Graph::add_edge(const size_t u, const size_t v) {
    _adj_list[u].push_back(v);
}

/**
 * get the neighbors of a given vertex
 *
 * @param u the vertex whose neighbors we would like
 * @return a const ref to the list of neighbors
*/
list<size_t> const & Graph::neighbors(const size_t u) const {
    return _adj_list[u];
}

/**
 * helper to print the edges of the graph
 */
void Graph::print_edges() const {
    for (size_t vertex = 0; vertex < _adj_list.size(); vertex++) {
        for (size_t neighbor : neighbors(vertex)) {
            cout << vertex << " " << neighbor << endl;
        }
    }
}

/**
 * get the vector of colors
 *
 * @return _colors
 */
vector<Color> Graph::get_colors() const {
    return _colors;
}

/**
 * detect if the graph is bipartite, and if so, colors each node appropriately
 * in _colors with each node set to BLUE or RED. If not, all nodes should be WHITE.
 *
 * @return true if graph is bipartite
 * @return false if graph is not bipartite
 */
bool Graph::is_bipartite() {
    std::fill(_colors.begin(), _colors.end(), WHITE);

    for (int start_node = 0; start_node < _adj_list.size(); ++start_node) {
        if (_colors[start_node] != WHITE) continue;

        std::queue<int> node_queue;
        node_queue.push(start_node);
        _colors[start_node] = RED;

        while (!node_queue.empty()) {
            int current_node = node_queue.front();
            node_queue.pop();

            Color current_color = _colors[current_node];
            Color neighbor_color;
            if (current_color == RED) {
                neighbor_color = BLUE;
            } else {
                neighbor_color = RED;
            }

            for (int neighbor : _adj_list[current_node]) {
                if (_colors[neighbor] == WHITE) {
                    _colors[neighbor] = neighbor_color;
                    node_queue.push(neighbor);
                } else if (_colors[neighbor] == current_color) {
                    std::fill(_colors.begin(), _colors.end(), WHITE);
                    return false;
                }
            }
        }
    }

    return true;
}
