graph=$1
landmark=$2
partition=$3
selected_queries=$4
runs=$5
QUERY=$1_$4.sh
echo Graph $graph Landmark $landmark Partition $partition

gpmetis $graph.metis $partition
./preprocess/landmark $graph $landmark
./preprocess/partition $graph $partition

cp $graph.lm2v landmark-vertex-matrix.txt
cp $graph.v2lm vertex-landmark-matrix.txt
cp $graph.pt   partition-bits.txt

bash start-neo4j.sh
head -10 $QUERY > tmp.sh
bash tmp.sh
rm tmp.sh
echo Start Experiment
bash run.sh $QUERY $runs $graph_$landmark_$partition
./neo4j stop

cat $graph_original_*.log $graph_$landmark_$partition_*.log | python analysis.py $selected_queries $runs > $graph_$landmark_$partition.sum 
