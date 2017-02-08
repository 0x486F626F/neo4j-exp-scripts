all: reindex landmark partition

lscc:
	g++ -o lscc -O2 util.cc tarjan.cc main-lscc.cc

reindex:
	g++ -o reindex -O2 main-reindex.cc reindex.cc util.cc select_landmark.cc 

landmark:
	g++ -o landmark -O2 main-landmark.cc util.cc landmark_matrix.cc select_landmark.cc

partition:
	g++ -o partition -O2 main-partition.cc util.cc partition_matrix.cc

clear:
	rm reindex landmark partition 
