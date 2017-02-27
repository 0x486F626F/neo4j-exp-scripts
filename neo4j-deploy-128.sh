wget static.hongbozhang.me/share/neo4j-community-3.0.6-SNAPSHOT-unix.tar.gz
tar zxvf neo4j-community-3.0.6-SNAPSHOT-unix.tar.gz
mv neo4j-community-3.0.6-SNAPSHOT neo4j
git clone https://github.com/hobozhang/neo4j-3.0.6.git
mv neo4j-3.0.6 src
cd src
mvn install -DskipTests -Dlicense.skip=true

cd community/graph-algo

git checkout exp-original
mvn install -DskipTests -Dlicense.skip=true
cp target/neo4j-graph-algo-3.0.6-SNAPSHOT.jar ../../../neo4j/lib/original.jar
chmod +x ../../../neo4j/lib/original.jar

git checkout exp-partition128
mvn install -DskipTests -Dlicense.skip=true
cp target/neo4j-graph-algo-3.0.6-SNAPSHOT.jar ../../../neo4j/lib/partition-landmark.jar
chmod +x ../../../neo4j/lib/partition-landmark.jar

cd ../../../neo4j/bin
git clone https://github.com/hobozhang/neo4j-exp-scripts.git
cd neo4j-exp-scripts/
git checkout 128-partition
cd ..
mv neo4j-exp-scripts/* .
rm neo4j-exp-scripts -rf

cd preprocess
make all
