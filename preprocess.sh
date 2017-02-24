graph=$1
total_queryies=$2
selected_queries=$3

./preprocess/reindex $graph

./neo4j stop
rm ../data/databases/graph.db -r
./neo4j-import --into ../data/databases/graph.db --nodes node.csv --relationships edge.csv

bash start-neo4j.sh

# create index on id
./neo4j-shell -c "CREATE INDEX ON :Vertex(id);"

size=`grep -vc '^$' node.csv`
bash generate-queries.sh $total_queryies $selected_queries $size $graph_$selected_queries.sh

./neo4j stop
