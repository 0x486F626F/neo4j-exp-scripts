#include "bfs.h"
#include "graph.h"

#include <iostream>
#include <map>
#include <queue>
#include <set>

static unsigned int dequeue_count;

static bool onelayer(std::queue <Node*> &cur_queue,
        std::map <unsigned int, unsigned int> &cur_map,
        std::set <unsigned int> &visited) {
    std::queue <Node*> next_queue;
    while (!cur_queue.empty()) {
        dequeue_count ++;
        Node* node = cur_queue.front();
        cur_queue.pop();
        unsigned int dist = cur_map[node->get_id()];
        std::vector <Node*> neighbors = node->get_neighbors();

        for (size_t i = 0; i < neighbors.size(); i ++) {
            unsigned int nid = neighbors[i]->get_id();
            if (cur_map.find(nid) == cur_map.end()) {
                next_queue.push(neighbors[i]);
                cur_map[nid] = dist + 1;
                if (visited.find(nid) != visited.end())
                    return true;
                visited.insert(nid);
            }
        }
    }
    while (!next_queue.empty()) {
        cur_queue.push(next_queue.front());
        next_queue.pop();
    }
    return false;
}

std::pair <int, unsigned int> do_bidirectional_bfs_one_shortest(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return std::make_pair(0, 0);
    dequeue_count = 0;

    std::queue <Node*> l_queue, r_queue;
    std::map <unsigned int, unsigned int> l_map, r_map;
    std::set <unsigned int> visited;

    l_queue.push(start), r_queue.push(end);
    l_map[start->get_id()] = r_map[end->get_id()] = 0;

    while (!l_queue.empty() || !r_queue.empty()) {
        if (r_queue.empty() || (l_queue.size() < r_queue.size() && l_queue.size())) {
            if (onelayer(l_queue, l_map, visited)) break;
        } else {
            if (onelayer(r_queue, r_map, visited)) break;
        }
    }

    unsigned int dist = 0xffffffff;
    for(std::map<unsigned int,unsigned int>::iterator it=l_map.begin();it!=l_map.end();it++)
        if (r_map.find(it->first) != r_map.end())
            dist = std::min(dist, r_map[it->first] + l_map[it->first]);
    return std::make_pair(int(dist), dequeue_count);
}
