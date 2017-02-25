GRAPH=$1
LANDMARK=$2
PARTITION=$3
TOPQUERY=$4
RUNS=$5
QUERY=$1_$4.sh
echo Graph $GRAPH Landmark $LANDMARK Partition $PARTITION

gpmetis $GRAPH.metis $PARTITION
./preprocess/LANDMARK $GRAPH $LANDMARK
./preprocess/PARTITION $GRAPH $PARTITION

cp $GRAPH.lm2v LANDMARK-vertex-matrix.txt
cp $GRAPH.v2lm vertex-LANDMARK-matrix.txt
cp $GRAPH.pt   PARTITION-bits.txt

bash start-neo4j.sh
head -10 $QUERY > tmp.sh
bash tmp.sh
rm tmp.sh

echo Start Experiment
NAME=$GRAPH_$LANDMARK_$PARTITION
bash run.sh $QUERY $RUNS $NAME
./neo4j stop

cat $GRAPH_original_*.log $NAME_*.log | python analysis.py $TOPQUERY $RUNS > $NAME.sum 
