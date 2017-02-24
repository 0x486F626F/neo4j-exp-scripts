cat /dev/null > ../logs/neo4j.log
./neo4j start
# wait neo4j to start
while [ true ]; do
    sleep 1
    log_len=`grep -vc '^$' ../logs/neo4j.log`
    if [ $(($log_len >= 4)) == 1 ]; then
        break  
    fi
done
sleep 10
cat /dev/null > ../logs/neo4j.log
