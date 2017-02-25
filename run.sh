SCRIPT=$1
RUNS=$2
PREFIX=$3
i=0
cat /dev/null > ../logs/neo4j.log
while [ $(($i < $RUNS)) == 1 ]; do
    bash $SCRIPT
    cp ../logs/neo4j.log $PREFIX-$i.log
    cat /dev/null > ../logs/neo4j.log
    i=$(($i + 1))
done
