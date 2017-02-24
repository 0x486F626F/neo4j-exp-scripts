graph=$1
total_queryies=$2
selected_queries=$3
runs=$4

cp ../lib/original.jar ../lib/neo4j-graph-algo-3.0.6-SNAPSHOT.jar
bash preprocess.sh $graph $total_queryies $selected_queries

bash start-neo4j.sh
bash run.sh $graph_$selected_queries.sh $runs $graph_original
./neo4j stop

cp ../lib/partition-landmark.jar ../lib/neo4j-graph-algo-3.0.6-SNAPSHOT.jar

bash experiment.sh $1 16 8 $3 $4
