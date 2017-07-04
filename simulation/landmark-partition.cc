#include "landmark-partition.h"

#include <iostream>
#include <fstream>

bool data_loaded = false;
std::vector <std::vector <int> > lm2v, v2lm;
std::vector <std::vector <long long> > part, rpart;
int ub;

void load_data() {
    data_loaded = true;
    std::cerr << "Loading Lamdmarks" << std::endl;
    int n, m, d;

    std::ifstream flm2v("lm2v.txt");
    flm2v >> n >> m;
    lm2v.push_back(std::vector <int> ());
    for (int i = 0; i < n; i ++) {
        std::vector <int> dist;
        for (int j = 0; j < m; j ++) {
            flm2v >> d;
            dist.push_back(d);
        }
        lm2v.push_back(dist);
    }

    std::ifstream fv2lm("v2lm.txt");
    fv2lm >> n >> m;
    v2lm.push_back(std::vector <int> ());
    for (int i = 0; i < n; i ++) {
        std::vector <int> dist;
        for (int j = 0; j < m; j ++) {
            fv2lm >> d;
            dist.push_back(d);
        }
        v2lm.push_back(dist);
    }

    int b, s;
    long long t;
    std::ifstream fpart("partition.txt");
    fpart >> b >> s >> n;
    part.push_back(std::vector <long long> ());
    rpart.push_back(std::vector <long long> ());
    for (int i = 0; i < n; i ++) {
        std::vector <long long> bits, rbits;
        for (int j = 0; j <= s; j ++) {
            fpart >> t;
            bits.push_back(t);
        }
        part.push_back(bits);
        for (int j = 0; j <= s; j ++) {
            fpart >> t;
            rbits.push_back(t);
        }
        rpart.push_back(rbits);
    }
    std::cerr << "data loaded " << lm2v.size() << " " << v2lm.size() << " " << 
        part.size() << " " << rpart.size() << std::endl;
}

int upperbound(int start_id, int end_id) {
    int result = v2lm.size();
    for (int i = 0; i < v2lm[start_id].size(); i ++)
        if (v2lm[start_id][i] >= 0 && lm2v[end_id][i] >= 0)
            result = std::min(result, v2lm[start_id][i] + lm2v[end_id][i]);
    return result;
}
