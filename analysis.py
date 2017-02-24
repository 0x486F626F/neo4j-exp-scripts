import sys

n = int(sys.argv[1])
m = int(sys.argv[2])

def average(arr):
    if (len(arr) >= 4):
        return (sum(arr) - max(arr) - min(arr)) / (len(arr) - 2)
    return sum(arr) / len(arr)

start = []
end = []
origin_node = []
origin_edge = []
origin_time = []
origin_avet = []

# original
for i in range(n):
    for j in range(m):
        row = raw_input().split()
        if (j == 0):
            start.append(int(row[0]))
            end.append(int(row[1]))
            origin_node.append(int(row[4]))
            origin_edge.append(int(row[5]))
            origin_time.append([])
        origin_time[i].append(int(row[3]))
    origin_avet.append(average(origin_time[i]))

node = []
edge = []
time = []
avet = []

# experiment
for i in range(n):
    for j in range(m):
        row = raw_input().split()
        if (j == 0):
            node.append(int(row[5]))
            edge.append(int(row[6]))
            time.append([])
        time[i].append(int(row[4]))
    avet.append(average(time[i]))

# Summary
origin_avet_mean = sum(origin_avet) / len(origin_avet)
avet_mean = sum(avet) / len(avet)

origin_node_mean = sum(origin_node) / len(origin_node)
node_mean = sum(node) / len(node)

origin_edge_mean = sum(origin_edge) / len(origin_edge)
edge_mean = sum(edge) / len(edge)

print "Original Node Ave: %d" % origin_node_mean
print "Experiment Node Ave: %d" % node_mean

print "Original Edge Ave: %d" % origin_edge_mean
print "Experiment Edge Ave: %d" % edge_mean

print "Original Time Ave: %d" % origin_avet_mean
print "Experiment Time Ave: %d" % avet_mean

for i in range(n):
    print "%d, %d, %d, %d, %d, %d, %d, %d" % (start[i], end[i], 
            origin_node[i], origin_edge[i], origin_avet[i],
            node[i], edge[i], avet[i])


