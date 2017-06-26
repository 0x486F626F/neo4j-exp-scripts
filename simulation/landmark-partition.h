#ifndef _LANDMARK_PARTITION_H_
#define _LANDMARK_PARTITION_H_

#include <vector>

extern bool data_loaded;
extern std::vector <std::vector <int> > lm2v, v2lm;
extern std::vector <std::vector <long long> > part, rpart;
extern int ub;

void load_data();
int upperbound(int start_id, int end_id);

#endif
