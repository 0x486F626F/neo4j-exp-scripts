#include "select_landmark.h"
#include "reindex.h"
#include "util.h"

#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        msg("./reindex graphname");
        return 1;
    }
    std::string graphname = argv[1];

    graphpair reindexed = reindex(graphname);
    graph dgraph = reindexed.first;
    graph ugraph = reindexed.second;
    select_high_degree_landmark(ugraph, 8);

    output_dgraph(dgraph, graphname);
    output_metis(ugraph, graphname);

    output_node_csv(dgraph);
    output_edge_csv(dgraph);

    return 0;
}
