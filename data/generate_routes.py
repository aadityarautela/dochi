"""
Assuming the graph is called "routeMap", and has a function addEdge which has the following signature

void addEdge(int u, int v, int weight)

and basically adds an undirected edge
"""

input_lines = []
with open("times.txt", "r") as f:
    input_lines = f.readlines()
output_lines = []
for line in input_lines:
    split_line = line.split()
    u = split_line[0]
    v = split_line[1]
    w = split_line[2]
    output_lines.append(f"routeMap.addEdge({u}, {v}, {w});\n")
with open("output_route.txt", "w") as f:
    f.writelines(output_lines)
