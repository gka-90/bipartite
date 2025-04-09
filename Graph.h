/**
    Recognizing Bipartite Graphs
    @file Graph.h
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

enum Color {WHITE, BLUE, RED};

std::ostream& operator<<(std::ostream& o, Color c);

class Graph {
public:
    Graph(const size_t num_vertices);
    void add_edge(const size_t u, const size_t v);
    std::list<size_t> const & neighbors(const size_t u) const;
    void print_edges() const;
    std::vector<Color> get_colors() const;
    bool is_bipartite();
private:
    std::vector<std::list<size_t>> _adj_list;
    std::vector<Color> _colors;
};

#endif // GRAPH_H
