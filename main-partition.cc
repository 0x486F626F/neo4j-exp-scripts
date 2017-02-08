#include "util.h"
#include "partition_matrix.h"

#include <string>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        msg("./partition graphname partitions");
        return 1;
    } 
    std::string graphname = argv[1];

    graph dgraph = load_dgraph(graphname);
    graph rgraph = reverse_graph(dgraph);

    std::vector <nodeid> partition = load_partition(graphname + ".metis.part." + argv[2]);
    partition_matrix part = compute_partition(std::make_pair(dgraph, rgraph), partition);
    output_partition_matrix(part, graphname);
}
