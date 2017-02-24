#include "select_landmark.h"

#include <algorithm>
#include <iostream>

std::vector <nodeid> select_high_degree_landmark(graph &ugraph, size_t size) {
    std::vector <std::pair <size_t, nodeid> > counter;
    for (size_t i = 0; i < ugraph.size(); i ++) 
        counter.push_back(std::make_pair(ugraph[i].size(), (nodeid)i + 1));
    std::sort(counter.begin(), counter.end());
    std::vector <nodeid> landmarks;
    for (size_t i = 0; i < size; i ++) 
        landmarks.push_back(counter[counter.size() - i - 1].second);
    return landmarks;
}

std::vector <nodeid> select_landmarks(graph &dgraph, graph &rgraph, size_t size) {
    std::vector <std::pair <size_t, nodeid> > counter;
    for (size_t i = 0; i < dgraph.size(); i ++) 
        counter.push_back(std::make_pair(dgraph[i].size() * rgraph[i].size(), (nodeid)i + 1));
    std::sort(counter.begin(), counter.end());
    std::vector <nodeid> landmarks;
    for (size_t i = 0; i < size; i ++) 
        landmarks.push_back(counter[counter.size() - i - 1].second);
    return landmarks;
}
