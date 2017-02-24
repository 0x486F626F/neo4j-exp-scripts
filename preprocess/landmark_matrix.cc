#include "landmark_matrix.h"
#include "util.h"

#include <queue>
#include <iostream>

landmark_matrix compute_landmark_matrix(graph& dgraph, std::vector <nodeid>& landmarks) {
    msg("Computing Landmark Matrix");
    landmark_matrix matrix(dgraph.size(), std::vector <int> (
                landmarks.size(), 0x3f3f3f3f));
    for (size_t i = 0; i < landmarks.size(); i ++) {
        progress_bar(i, landmarks.size());
        std::queue <nodeid> q;
        q.push(landmarks[i] - 1);
        matrix[landmarks[i] - 1][i] = 0;
        while (!q.empty()) {
            nodeid curr = q.front();
            q.pop();
            for (size_t j = 0; j < dgraph[curr].size(); j ++) {
                nodeid next = dgraph[curr][j] - 1;
                if (matrix[curr][i] + 1 < matrix[next][i]) {
                    matrix[next][i] = matrix[curr][i] + 1;
                    q.push(next);
                }
            }
        }
    }
    return matrix;
}
