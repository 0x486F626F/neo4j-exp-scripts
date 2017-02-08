#include "util.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

graph reverse_graph(graph& forward) {
    graph backward;
    for (size_t i = 0; i < forward.size(); i ++) 
        for (size_t j = 0; j < forward[i].size(); j ++) {
            while (backward.size() < forward[i][j]) 
                backward.push_back(std::vector <nodeid> ());
            backward[forward[i][j] - 1].push_back((nodeid)i + 1);
        }
    return backward;
}

size_t str_to_size(std::string str) {
    std::istringstream strin(str);
    size_t size;
    strin >> size;
    return size;
}

std::vector <nodeid> load_partition(std::string partitionfile) {
    std::ifstream fin(partitionfile.c_str());
    std::vector <nodeid> partition;
    nodeid part;
    while (fin >> part) partition.push_back(part);
    return partition;
}

void msg(std::string m) {
    std::cerr << m << std::endl;
}

void progress_bar(size_t cur, size_t tot) {
    static size_t cnt = 100;
    size_t pct = ((cur + 1) * 100) / tot;
    if (pct < cnt) {
        for (size_t i = 0; i < cnt - 1; i ++)
            if (i % (cnt >> 2) == 0) std::cerr << "|";
            else std::cerr << " ";
        std::cerr << "|" << std::endl;
        cnt = 0;
    }
    while (cnt < pct) cnt ++, std::cerr << "+";
    if (cur + 1 == tot) std::cerr << std::endl;
}

graph load_dgraph(std::string graphname) {
    msg("Load " + graphname + ".dg");
    std::ifstream fin((graphname + ".dg").c_str());
    graph dgraph;
    nodeid v1, v2;
    while (fin >> v1 >> v2) {
        size_t cursize = std::max(v1, v2);
        while (dgraph.size() <= cursize)
            dgraph.push_back(std::vector <nodeid> ());
        dgraph[v1 - 1].push_back(v2);
    }
    return dgraph;
}

void output_dgraph(graph& dgraph, std::string graphname) {
    msg("Output " + graphname + ".dg");
    std::ofstream fout((graphname + ".dg").c_str());
    for (size_t i = 0; i < dgraph.size(); i ++) {
        progress_bar(i, dgraph.size());
        for (size_t j = 0; j < dgraph[i].size(); j ++)
            fout << i + 1 << " " << dgraph[i][j] << std::endl;
    }
}

void output_metis(graph& ugraph, std::string graphname) {
    msg("Output " + graphname + ".metis");
    std::ofstream fout((graphname + ".metis").c_str());
    size_t edge = 0;
    for (size_t i = 0; i < ugraph.size(); i ++)
        edge += ugraph[i].size();
    fout << ugraph.size() << " " << edge / 2 << std::endl;
    for (size_t i = 0; i < ugraph.size(); i ++) {
        progress_bar(i, ugraph.size());
        for (size_t j = 0; j < ugraph[i].size(); j ++)
            fout << ugraph[i][j] << " ";
        fout << std::endl;
    }
}

void output_landmarks(std::vector <nodeid> &landmarks, std::string graphname) {
    std::ofstream fout((graphname + ".lm").c_str());
    for (size_t i = 0; i < landmarks.size(); i ++)
        fout << landmarks[i] << std::endl;
}

std::vector <nodeid> load_landmarks(std::string graphname) {
    msg("Load " + graphname + ".lm");
    std::ifstream fin((graphname + ".lm").c_str());
    std::vector <nodeid> landmarks;
    nodeid v;
    while (fin >> v) landmarks.push_back(v);
    return landmarks;
}

void output_landmark_matrix(landmark_matrix& matrix, std::string graphname) {
    msg("Output Landmark Matrix " + graphname);
    std::ofstream fout(graphname.c_str());
    fout << matrix.size() << " " << matrix[0].size() << std::endl;
    for (size_t i = 0; i < matrix.size(); i ++) {
        progress_bar(i, matrix.size());
        for (size_t j = 0; j < matrix[i].size(); j ++)
            if (matrix[i][j] == 0x3f3f3f3f) fout << "-1 ";
            else fout << matrix[i][j] << " ";
        fout << std::endl;
    }
}

void output_partition_matrix(partition_matrix& matrix, std::string graphname) {
    msg("Output Partition " + graphname);
    std::ofstream fout((graphname + ".pt").c_str());
    fout << "64 2 " << matrix.size() << std::endl;
    for (size_t i = 0; i < matrix.size(); i ++) {
        progress_bar(i, matrix.size());
        fout << matrix[i][0].str() << " " << matrix[i][1].str() << " " << matrix[i][2].str() << std::endl;
        fout << matrix[i][0].str() << " " << matrix[i][3].str() << " " << matrix[i][4].str() << std::endl;
    }
}

void output_edge_csv(graph& dgraph) {
    msg("Output edge.csv");
    std::ofstream fout("edge.csv");
    fout << ":START_ID,:END_ID,:TYPE" << std::endl;
    for (size_t i = 0; i < dgraph.size(); i ++) {
        progress_bar(i, dgraph.size());
        for (size_t j = 0; j < dgraph[i].size(); j ++)
            fout << i + 1 << "," << dgraph[i][j] << ",DIRECTED" << std::endl;
    }
}

void output_node_csv(graph& dgraph) {
    msg("Output node.csv");
    std::ofstream fout("node.csv");
    fout << "vertexId:Id,id:int,:LABEL" << std::endl;
    fout << "0,0,Vertex" << std::endl;
    for (size_t i = 0; i < dgraph.size(); i ++) {
        progress_bar(i, dgraph.size());
        fout << i + 1 << "," << i + 1 << ",Vertex" << std::endl;
    }
}

bitset128::bitset128() {
    s[0] = s[1] = 0;
}

void bitset128::set(size_t idx) {
    if (idx < 64) s[0] |= ((long long)1 << idx);
    else s[1] |= ((long long)1 << (idx - 64));
}

std::string bitset128::str() {
    std::ostringstream strout;
    strout << s[0] << " " << s[1];
    return strout.str();
}
