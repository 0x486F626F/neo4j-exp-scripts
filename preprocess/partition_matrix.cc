#include "partition_matrix.h"
#include "util.h"

static bitset128 onestep(graph& dgraph, nodeid source, std::vector <nodeid>& partition) {
    bitset128 neighbor;
    neighbor.set(partition[source]);
    for (size_t i = 0; i < dgraph[source].size(); i ++) {
        nodeid next = dgraph[source][i] - 1;
        neighbor.set(partition[next]);
    }
    return neighbor;
}

static bitset128 twostep(graph& dgraph, nodeid source, std::vector <nodeid>& partition) {
    bitset128 neighbor;
    neighbor.set(partition[source]);
    for (size_t i = 0; i < dgraph[source].size(); i ++) {
        nodeid next = dgraph[source][i] - 1;
        neighbor.set(partition[next]);
        for (size_t j = 0; j < dgraph[next].size(); j ++) {
            nodeid nextnext = dgraph[next][j] - 1;
            neighbor.set(partition[nextnext]);
        }
    }
    return neighbor;
}

partition_matrix compute_partition(graphpair dgraph, std::vector <nodeid>& partition) {
    msg("Computing Partition");
    partition_matrix matrix;
    for (size_t i = 0; i < dgraph.first.size(); i ++) {
        progress_bar(i, dgraph.first.size());
        std::vector <bitset128> curr;
        bitset128 self;
        self.set(partition[i]);
        curr.push_back(self);
        curr.push_back(onestep(dgraph.first, (nodeid)i, partition));
        curr.push_back(twostep(dgraph.first, (nodeid)i, partition));
        curr.push_back(onestep(dgraph.second, (nodeid)i, partition));
        curr.push_back(twostep(dgraph.second, (nodeid)i, partition));
        matrix.push_back(curr);
    }
    return matrix;
}
