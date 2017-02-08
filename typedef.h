#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vector>

typedef unsigned int nodeid;
typedef long long bitset64;
typedef std::vector <std::vector <nodeid> > graph;
typedef std::pair <graph, graph> graphpair;
typedef std::vector <std::vector <int> > landmark_matrix;
typedef std::vector <std::vector <bitset64> > partition_matrix;

#endif
