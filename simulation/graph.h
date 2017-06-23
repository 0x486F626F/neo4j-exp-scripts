#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <string>

#include <stdlib.h>

class Node {
    private:
        unsigned int id;
        std::vector <Node*> neighbors;

        std::vector <Node*> sorted_neighbors;
        bool is_sorting_updated;
        
    public:
        Node(unsigned int id);

        void add_neighbor(Node* neighbor);

        unsigned int get_id() const;
        size_t get_out_degree() const;

        std::vector <Node*> &get_neighbors();
        std::vector <Node*> &get_sorted_neibors();
};

typedef std::vector <Node*> Graph;

struct DirectedGraph {
    Graph fgraph;
    Graph rgraph;

    DirectedGraph(std::string filename, bool undirected = false);
    ~DirectedGraph();
};

#endif
