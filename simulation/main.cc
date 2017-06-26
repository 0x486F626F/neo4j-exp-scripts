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
        int truedist = bfs(g.fgraph[l], g.rgraph[r]); 
        std::cerr << truedist << std::endl;
        std::vector <int> result;

        result = bidirectional_bfs_one_shortest(g.fgraph[l], g.rgraph[r]);
        std::cerr << "bi-directional bfs" << std::endl;
        std::cout << result[0] << "  " << result[1] << std::endl;
        if (result[0] != truedist) break;

        result = do_bidirectional_bfs_one_shortest(g.fgraph[l], g.rgraph[r]);
        std::cerr << "directional optimized bi-directional bfs" << std::endl;
        std::cout << result[0] << "  " << result[1] << std::endl;
        if (result[0] != truedist) break;

        result = bidirectional_bfs_lp_one_shortest(g.fgraph[l], g.rgraph[r]);
        std::cerr << "bi-directional bfs landmark partition" << std::endl;
        std::cout << result[0] << "  " << result[1] << std::endl;
        if (result[0] != truedist) break;

        result = do_bidirectional_bfs_lp_one_shortest(g.fgraph[l], g.rgraph[r]);
        std::cerr << "directional optimized bi-directional bfs landmark partition" << std::endl;
        std::cout << result[0] << "  " << result[1] << std::endl;
        if (result[0] != truedist) break;

        std::cerr << "===========================================" << std::endl;
    }
    return 0;
}
