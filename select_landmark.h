#ifndef SELECT_LANDMARK_H
#define SELECT_LANDMARK_H

#include "typedef.h"

#include <vector>
#include <stddef.h>

std::vector <nodeid> select_high_degree_landmark(graph &ugraph, size_t size);

std::vector <nodeid> select_landmarks(graph &dgraph, graph &rgraph, size_t size);

#endif
