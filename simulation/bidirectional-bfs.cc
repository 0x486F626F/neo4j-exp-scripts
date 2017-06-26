#include "bfs.h"
#include "graph.h"
#include "landmark-partition.h"

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

std::vector <int> bidirectional_bfs_one_shortest(Node* start, Node* end) {
    if (start->get_id() == end->get_id()) return std::vector <int> (2, 0);
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
    std::vector <int> result;
    result.push_back(int(dist));
    result.push_back(int(dequeue_count));
    return result;
}

static bool onestep_lp(std::queue <Node*> &cur_queue,
        std::queue <Node*> &next_queue,
        std::map <unsigned int, unsigned int> &cur_map,
        std::set <unsigned int> &visited,
        bool next_layer,
        int end_id, bool start_side) {
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
    
    int sid, tid;
    if (start_side) sid = node->get_id(), tid = end_id;
    else sid = end_id, tid = node->get_id();
    int min_lb = ub - dist + 1;
    if (min_lb == 1 && sid != tid) return false;
    else {
        //std::cerr << "Need: " << min_lb << std::endl;
        int l = std::max(0, min_lb-int(part[1].size())), u = std::min(int(part[1].size()), min_lb);
        for (int i = l; i < u; i ++) {
            int j = min_lb - i - 1;
            //std::cerr << dist << " " << ub << " " << min_lb << std::endl;
            if ((part[sid][i] & rpart[tid][j]) == 0) return false;
        }
    }

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

std::vector <int> bidirectional_bfs_lp_one_shortest(Node* start, Node* end) {
    if (!data_loaded) load_data();
    if (start->get_id() == end->get_id()) return std::vector <int> (2, 0);
    ub = upperbound(start->get_id(), end->get_id());
    dequeue_count = 0;

    std::queue <Node*> l_queue, r_queue, l_next, r_next;
    std::map <unsigned int, unsigned int> l_map, r_map;
    std::set <unsigned int> visited;

    l_queue.push(start), r_queue.push(end);
    l_map[start->get_id()] = r_map[end->get_id()] = 0;

    while (!l_queue.empty() || !r_queue.empty() || !l_next.empty() || !r_next.empty()) {
        if (onestep_lp(l_queue, l_next, l_map, visited, true, end->get_id(), true)) {
            while (!r_queue.empty()) onestep_lp(r_queue, r_next, r_map, visited, false, end->get_id(), false);
            break;
        }
        if (onestep_lp(r_queue, r_next, r_map, visited, true, end->get_id(), false)) {
            while (!l_queue.empty()) onestep_lp(l_queue, l_next, l_map, visited, false, end->get_id(), true);
            break;
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
