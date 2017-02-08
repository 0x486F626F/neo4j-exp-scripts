#ifndef UTIL_H
#define UTIL_H

#include "typedef.h"

#include <string>
#include <vector>

struct bitset128 {
    bitset64 s[2];
    bitset128();
    void set(size_t idx);
    std::string str();
};

typedef std::vector <std::vector <bitset128> > partition_matrix;

graph reverse_graph(graph& forward);

size_t str_to_size(std::string str);

std::vector <nodeid> load_partition(std::string partitionfile);

void msg(std::string m);

void progress_bar(size_t cur, size_t tot);

graph load_dgraph(std::string graphname);

void output_dgraph(graph& dgraph, std::string graphname);

void output_metis(graph& ugraph, std::string graphname);

void output_landmarks(std::vector <nodeid> &landmarks, std::string graphname);

std::vector <nodeid> load_landmarks(std::string graphname);

void output_landmark_matrix(landmark_matrix& matrix, std::string graphname);

void output_partition_matrix(partition_matrix& matrix, std::string graphname);

void output_edge_csv(graph& dgraph);

void output_node_csv(graph& dgraph);

#endif
