#include "bfs.h"
#include "graph.h"
#include "landmark-partition.h"

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

std::vector <int> do_bidirectional_bfs_one_shortest(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return std::vector <int> (2, 0);
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
    std::vector <int> result;
    result.push_back(int(dist));
    result.push_back(int(dequeue_count));
    return result;
}


static bool onelayer_lp(std::queue <Node*> &cur_queue,
        std::map <unsigned int, unsigned int> &cur_map,
        std::set <unsigned int> &visited,
        int end_id, bool start_side) {
    std::queue <Node*> next_queue;
    while (!cur_queue.empty()) {
        dequeue_count ++;
        Node* node = cur_queue.front();
        cur_queue.pop();
        unsigned int dist = cur_map[node->get_id()];

        int sid, tid;
        if (start_side) sid = node->get_id(), tid = end_id;
        else sid = end_id, tid = node->get_id();
        int min_lb = ub - dist + 1;
        bool outofbound = false;
        if (min_lb == 1 && sid != tid) outofbound = true;
        else {
            int l = std::max(0, min_lb-int(part[1].size())), u = std::min(int(part[1].size()), min_lb);
            for (int i = l; i < u; i ++) {
                int j = min_lb - i - 1;
                if ((part[sid][i] & rpart[tid][j]) == 0) {
                    std::cerr << dist << " " << ub << " " << min_lb << std::endl;
                    outofbound = true;
                    break;
                }
            }
        }
        if (outofbound) continue;

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

std::vector <int> do_bidirectional_bfs_lp_one_shortest(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return std::vector <int> (2, 0);
    dequeue_count = 0;

    std::queue <Node*> l_queue, r_queue;
    std::map <unsigned int, unsigned int> l_map, r_map;
    std::set <unsigned int> visited;

    l_queue.push(start), r_queue.push(end);
    l_map[start->get_id()] = r_map[end->get_id()] = 0;

    while (!l_queue.empty() || !r_queue.empty()) {
        if (r_queue.empty() || (l_queue.size() < r_queue.size() && l_queue.size())) {
            if (onelayer_lp(l_queue, l_map, visited, end->get_id(), true)) break;
        } else {
            if (onelayer_lp(r_queue, r_map, visited, end->get_id(), false)) break;
        }
    }

    unsigned int dist = 0xffffffff;
    for(std::map<unsigned int,unsigned int>::iterator it=l_map.begin();it!=l_map.end();it++)
        if (r_map.find(it->first) != r_map.end())
            dist = std::min(dist, r_map[it->first] + l_map[it->first]);
    std::vector <int> result;
    result.push_back(int(dist));
    result.push_back(int(dequeue_count));
    return result;
}
