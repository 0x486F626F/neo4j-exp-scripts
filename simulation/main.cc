#include "graph.h"
#include "bfs.h"

#include <fstream>
#include <iostream>

int main() {
    DirectedGraph g("web.edge");
    std::cerr << "Graph Loaded " << g.fgraph.size() << std::endl;

    std::ifstream fin("query.txt");
    unsigned int l, r;
    for (int i = 0; i < 1000; i ++) {
        fin >> l >> r;
        std::cerr << "Query " << i + 1 << ": From " << l << " To " << r << std::endl;
        int d1 = bfs(g.fgraph[l], g.rgraph[r]); 
        std::pair <int, unsigned int> d2 = bidirectional_bfs_one_shortest(g.fgraph[l], g.rgraph[r]);
        std::cout << d1 << std::endl;
        std::cout << d2.first << " " << d2.second << std::endl;

        if (d1 != d2.first) break;
    }
    return 0;
}
