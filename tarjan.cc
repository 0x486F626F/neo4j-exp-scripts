#include "tarjan.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>

#include <stdlib.h>

static void dfs(nodeid u, graph &dgraph, std::set <nodeid> &lscc, 
        std::vector <int> &dfn, std::vector <int> &low, 
        std::stack <nodeid> &stk, std::vector <bool> &ins, int &stamp) {
    dfn[u] = low[u] = ++ stamp;
    stk.push(u);
    ins[u] = true;
    for (size_t i = 0; i < dgraph[u].size(); i ++) {
        nodeid v =dgraph[u][i];
        if (dfn[v] == 0) {
            dfs(v, dgraph, lscc, dfn, low, stk, ins, stamp);
            low[u] = std::min(low[u], low[v]);
        }
        else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        std::set <nodeid> scc;
        nodeid v;
        do {
            v = stk.top();
            stk.pop();
            ins[v] = false;
            scc.insert(v);
        } while (u != v);
        if (scc.size() > lscc.size()) lscc = scc;
    }
}

static std::set <nodeid> find_lscc(graph &dgraph) {
    std::vector <int> dfn(dgraph.size(), 0);
    std::vector <int> low(dgraph.size(), 0);
    std::vector <bool> ins(dgraph.size(), false);
    std::stack <nodeid> stk, call_stack;
    std::set <nodeid> lscc;
    int stamp = 0;
    for (nodeid i = 0; i < dgraph.size(); i ++)
        if (dfn[i] == 0 && dgraph[i].size()) {
            call_stack.push(i);
            dfn[i] = low[i] = ++ stamp;
            stk.push(i);
            ins[i] = true;
            while (!call_stack.empty()) {
                nodeid u = call_stack.top();
                for (size_t j = 0; j < dgraph[u].size(); j ++) {
                    nodeid v = dgraph[u][j];
                    if (dfn[v] == 0) {
                        call_stack.push(v);
                        dfn[v] = low[v] = ++ stamp;
                        stk.push(v);
                        ins[v] = true;
                        break;
                    }
                }
                if (u == call_stack.top()) {
                    for (size_t j = 0; j < dgraph[u].size(); j ++) {
                        nodeid v = dgraph[u][j];
                        if (dfn[v] > dfn[u]) low[u] =std::min(low[u], low[v]);
                        else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
                    }
                    if (dfn[u] == low[u]) {
                        std::set <nodeid> scc;
                        nodeid v;
                        do {
                            v = stk.top();
                            stk.pop();
                            ins[v] = false;
                            scc.insert(v);
                        } while (u != v);
                        if (scc.size() > lscc.size()) lscc = scc;
                    }
                    call_stack.pop();
                }
            }
        }
    return lscc;
}

std::vector <std::pair <nodeid, nodeid> > tarjan(std::string &graphname) {
    std::ifstream fin((graphname + ".txt").c_str());
    graph dgraph;
    nodeid v1, v2;
    while (fin >> v1 >> v2) {
        size_t cursize = std::max(v1, v2);
        while (dgraph.size() <= cursize)
            dgraph.push_back(std::vector <nodeid> ());
        dgraph[v1].push_back(v2);
    }

    std::vector <int> dfn(dgraph.size(), 0);
    std::vector <int> low(dgraph.size(), 0);
    std::vector <bool> ins(dgraph.size(), false);
    std::stack <nodeid> stk;
    std::set <nodeid> lscc = find_lscc(dgraph);
    std::cerr << "Graph Size: " << dgraph.size() 
        << " LSCC Size: " << lscc.size() << std::endl;
    std::vector <std::pair <nodeid, nodeid> > edges;
    for (nodeid i = 0; i < dgraph.size(); i ++)
        if (lscc.find(i) != lscc.end()) 
            for (size_t j = 0; j < dgraph[i].size(); j ++)
                if (lscc.find(dgraph[i][j]) != lscc.end())
                    edges.push_back(std::make_pair(i, dgraph[i][j]));
    return edges;
}
