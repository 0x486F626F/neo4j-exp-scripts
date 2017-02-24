scirpt=$1
runs=$2
prefix=$3
i=0
cat /dev/null > ../logs/neo4j.log
while [ $(($i < $runs)) == 1 ]; do
    bash $scirpt
    cp ../logs/neo4j.log $prefix_$i.log
    cat /dev/null > ../logs/neo4j.log
    i=$(($i + 1))
done
