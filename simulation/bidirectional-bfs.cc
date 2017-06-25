#include "bfs.h"
#include "graph.h"

#include <iostream>
#include <map>
#include <queue>
#include <set>

static unsigned int dequeue_count;

static bool onestep(std::queue <Node*> &cur_queue,
        std::queue <Node*> &next_queue,
        std::map <unsigned int, unsigned int> &cur_map,
        std::set <unsigned int> &visited,
        bool next_layer = true) {
    if (cur_queue.empty()) {
        if (next_queue.empty()) return false;
        if (next_layer) {
            while (!next_queue.empty()) {
                cur_queue.push(next_queue.front());
                next_queue.pop();
            }
        }
    }

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
            if (visited.find(nid) == visited.end())
                visited.insert(nid);
            else if(next_layer) return true;
        }
    }
    return false;
}

std::pair <int, unsigned int> bidirectional_bfs_one_shortest(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return std::make_pair(0, 0);
    dequeue_count = 0;

    std::queue <Node*> l_queue, r_queue, l_next, r_next;
    std::map <unsigned int, unsigned int> l_map, r_map;
    std::set <unsigned int> visited;

    l_queue.push(start), r_queue.push(end);
    l_map[start->get_id()] = r_map[end->get_id()] = 0;

    while (!l_queue.empty() || !r_queue.empty() || !l_next.empty() || !r_next.empty()) {
        if (onestep(l_queue, l_next, l_map, visited)) {
            while (!r_queue.empty()) onestep(r_queue, r_next, r_map, visited, false);
            break;
        }
        if (onestep(r_queue, r_next, r_map, visited)) {
            while (!l_queue.empty()) onestep(l_queue, l_next, l_map, visited, false);
            break;
        }
    }


    unsigned int dist = 0xffffffff;
    for(std::map<unsigned int,unsigned int>::iterator it=l_map.begin();it!=l_map.end();it++)
        if (r_map.find(it->first) != r_map.end())
            dist = std::min(dist, r_map[it->first] + l_map[it->first]);
    return std::make_pair(int(dist), dequeue_count);
}


