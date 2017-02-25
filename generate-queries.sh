i=0
ALLQUERY=$1
TOPQUERY=$2
NODESIZE=$3
SCRIPT=$4
echo $1 $2 $3 $4

cat /dev/null > ../logs/neo4j.log
while [ $(($i < $ALLQUERY)) == 1 ]; do
    r1=$((($RANDOM * 32768) + $RANDOM))
    r2=$((($RANDOM * 32768) + $RANDOM))
    s=$(($r1 % $NODESIZE)) 
    t=$(($r2 % $NODESIZE)) 
    echo Query $i $s $t
    bash ./neo4j-shell -c "MATCH p$i=allShortestPaths((start:Vertex{id:$s})-[*]->(end:Vertex{id:$t})) RETURN p$i;" > /dev/null 2> /dev/null
    tail -1 ../logs/neo4j.log
    i=$(($i + 1))
done

python select-queries.py $ALLQUERY $TOPQUERY < ../logs/neo4j.log > $SCRIPT
