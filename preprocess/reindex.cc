#include "reindex.h"
#include "util.h"

#include <fstream>
#include <vector>
#include <set>

graphpair reindex(std::string graphname) {
    msg("Re-indexing Graph");

    std::ifstream fin((graphname + ".edge").c_str());
    std::vector <std::set <nodeid> > u_unique, d_unique;
    nodeid v1, v2;
    while (fin >> v1 >> v2) 
        if (v1 != v2) {
            size_t cursize = std::max(v1, v2);
            while (u_unique.size() <= cursize) 
                u_unique.push_back(std::set <nodeid> ());
            u_unique[v1].insert(v2);
            u_unique[v2].insert(v1);

            while (d_unique.size() <= cursize)
                d_unique.push_back(std::set <nodeid> ());
            d_unique[v1].insert(v2);
        }

    std::vector <nodeid> empty_nodes;
    for (nodeid i = 0; i < u_unique.size(); i ++)
        if (u_unique[i].size() == 0) empty_nodes.push_back(i);
    graph ugraph, dgraph;
    for (size_t i = 0; i < u_unique.size(); i ++)
        if (u_unique[i].size()) {
            progress_bar(i, u_unique.size());
            std::vector <nodeid> curr;
            for (std::set <nodeid>::iterator it = u_unique[i].begin(); it != u_unique[i].end(); it ++) {
                size_t offset = (std::lower_bound(empty_nodes.begin(), empty_nodes.end(), *it) 
                        - empty_nodes.begin());
                curr.push_back(*it - (nodeid)offset + 1);
            }
            ugraph.push_back(curr);

            curr.clear();
            for (std::set <nodeid>::iterator it = d_unique[i].begin(); it != d_unique[i].end(); it ++) {
                size_t offset = (std::lower_bound(empty_nodes.begin(), empty_nodes.end(), *it)
                        - empty_nodes.begin());
                curr.push_back(*it - (nodeid)offset + 1);
            }
            dgraph.push_back(curr);
        }
    return std::make_pair(dgraph, ugraph);
}
