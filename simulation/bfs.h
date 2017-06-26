#ifndef __BFS_H__
#define __BFS_H__

#include "graph.h"

unsigned int bfs(Node* start, Node* end);
std::vector <int> bidirectional_bfs_one_shortest(Node* start, Node* end);
std::vector <int> bidirectional_bfs_lp_one_shortest(Node* start, Node* end);
std::vector <int> do_bidirectional_bfs_one_shortest(Node* start, Node* end);
std::vector <int> do_bidirectional_bfs_lp_one_shortest(Node* start, Node* end);

#endif
