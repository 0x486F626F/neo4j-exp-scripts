i=0
total_queryies=$1
selected_queries=$2
node_size=$3
output_script=$4
echo $1 $2 $3 $4

cat /dev/null > ../logs/neo4j.log
while [ $(($i < $total_queryies)) == 1 ]; do
    r1=$((($RANDOM * 32768) + $RANDOM))
    r2=$((($RANDOM * 32768) + $RANDOM))
    s=$(($r1 % $node_size)) 
    t=$(($r2 % $node_size)) 
    echo Query $i $s $t
    bash ./neo4j-shell -c "MATCH p$i=allShortestPaths((start:Vertex{id:$s})-[*]->(end:Vertex{id:$t})) RETURN p$i;" > /dev/null 2> /dev/null
    tail -1 ../logs/neo4j.log
    i=$(($i + 1))
done

cp ../logs/neo4j.log .
python select-queries.py $total_queryies $selected_queries < ../logs/neo4j.log > $output_script
