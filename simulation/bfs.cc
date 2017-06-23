#include "graph.h"

#include <queue>
#include <map>

unsigned int bfs(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return 0;

    std::queue <Node*> l_queue;
    std::map <unsigned int, unsigned int> l_dist;

    l_queue.push(start);
    l_dist[start->get_id()] = 0;

    while (!l_queue.empty()) {
        Node* cur_node = l_queue.front();
        l_queue.pop();

        unsigned int cur_dist = l_dist[cur_node->get_id()];
        std::vector <Node*> neighbors = cur_node->get_neighbors();
        for (size_t i = 0; i < neighbors.size(); i ++)
            if (l_dist.find(neighbors[i]->get_id()) == l_dist.end()) {
                l_queue.push(neighbors[i]);
                l_dist[neighbors[i]->get_id()] = cur_dist + 1;
                if (neighbors[i]->get_id() == end->get_id()) return l_dist[end->get_id()];
            }
    }
    return 0xffffffff;
}
