#include "util.h"
#include "landmark_matrix.h"
#include "select_landmark.h"

#include <string>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        msg("./landmark graphname landmarks");
        return 1;
    }
    std::string graphname = argv[1];
    size_t landmark_size = str_to_size(argv[2]);
    
    graph dgraph = load_dgraph(graphname);
    graph rgraph = reverse_graph(dgraph);
    std::vector <nodeid> landmarks = select_landmarks(dgraph, rgraph, landmark_size);
    output_landmarks(landmarks, graphname);

    landmark_matrix lm2v = compute_landmark_matrix(dgraph, landmarks);
    output_landmark_matrix(lm2v, graphname + ".lm2v"); 
    landmark_matrix v2lm = compute_landmark_matrix(rgraph, landmarks);
    output_landmark_matrix(v2lm, graphname + ".v2lm");    

    return 0;
}
