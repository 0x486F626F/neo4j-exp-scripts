import sys

n = int(sys.argv[1])
m = int(sys.argv[2])
a = []
for i in range(n):
    line = raw_input().split()
    s = int(line[0])
    t = int(line[1])
    e = int(line[5])
    a.append([-e, s, t])
a = sorted(a)[:m]
for i in range(m):
    print 'echo Query ' + str(i)
    print './neo4j-shell -c "MATCH p%d=allShortestPaths((start:Vertex{id:%d})-[*]->(end:Vertex{id:%d})) RETURN p%d;" > /dev/null 2> /dev/null' % (i, a[i][1], a[i][2], i)
print 'echo End'
