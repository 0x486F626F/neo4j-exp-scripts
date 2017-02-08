#include "util.h"
#include "tarjan.h"

#include <fstream>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        msg("./lscc graphname");
        return 1;
    }
    std::string graphname =argv[1];

    std::vector <std::pair <nodeid, nodeid> > edges = tarjan(graphname);
    std::ofstream fout((graphname + ".edge").c_str());
    for (size_t i = 0; i < edges.size(); i ++)
        fout << edges[i].first << " " << edges[i].second << std::endl;
    return 0;
}
