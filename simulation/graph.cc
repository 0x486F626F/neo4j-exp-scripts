#include "graph.h"

#include <fstream>
#include <algorithm>
#include <vector>

Node::Node(unsigned int id): id(id), is_sorting_updated(false) {}

void Node::add_neighbor(Node* neighbor) {
    is_sorting_updated = false;
    neighbors.push_back(neighbor);
}

unsigned int Node::get_id() const { return id; }
size_t Node::get_out_degree() const { return neighbors.size(); }

std::vector <Node*> &Node::get_neighbors() { return neighbors; }
std::vector <Node*> &Node::get_sorted_neibors() {
    if (is_sorting_updated) return sorted_neighbors;

    std::vector <std::pair <unsigned int, Node*> > ranking;
    for (size_t i = 0; i < neighbors.size(); i ++) 
        ranking.push_back(std::make_pair(neighbors[i]->get_out_degree(), neighbors[i]));
    std::sort(ranking.begin(), ranking.end());

    sorted_neighbors.clear();
    for (size_t i = 0; i < ranking.size(); i ++)
        sorted_neighbors.push_back(ranking[ranking.size() - i - 1].second);
    is_sorting_updated = true;

    return sorted_neighbors;
}


DirectedGraph::DirectedGraph(std::string filename, bool undirected) {
    std::ifstream fin(filename.c_str());
    unsigned int l, r;
    while (fin >> l >> r) {
        while (fgraph.size() <= std::max(l, r)) {
            fgraph.push_back(new Node((unsigned int)fgraph.size()));
            rgraph.push_back(new Node((unsigned int)rgraph.size()));
        }
        fgraph[l]->add_neighbor(fgraph[r]);
        rgraph[r]->add_neighbor(rgraph[l]);
        if (undirected) {
            fgraph[r]->add_neighbor(fgraph[l]);
            rgraph[l]->add_neighbor(rgraph[r]);
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (size_t i = 0; i < fgraph.size(); i ++)
        delete fgraph[i];
    for (size_t i = 0; i < rgraph.size(); i ++)
        delete rgraph[i];
}
