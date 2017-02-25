GRAPH=$1
ALLQUERY=$2
TOPQUERY=$3
runs=$4

cp ../lib/original.jar ../lib/neo4j-GRAPH-algo-3.0.6-SNAPSHOT.jar
bash preprocess.sh $GRAPH $ALLQUERY $TOPQUERY

bash start-neo4j.sh
bash run.sh $GRAPH_$TOPQUERY.sh $runs $GRAPH_original
./neo4j stop

cp ../lib/partition-landmark.jar ../lib/neo4j-GRAPH-algo-3.0.6-SNAPSHOT.jar

bash experiment.sh $1 16 8 $3 $4
