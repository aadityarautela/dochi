"""
Assuming the Station structure looks like the following

struct Station{
    int id;
    string name;
}

and the stations lookup vector is simply called "stations"
"""


input_lines = []
with open("stations.txt", "r") as f:
    input_lines = f.readlines()
output_lines = []
for line in input_lines:
    split_line = line.split()
    station_id = split_line[0]
    station_name = " ".join(split_line[1:])
    output_lines.append(f"stations[{station_id}].id = {station_id};\n")
    output_lines.append(f"stations[{station_id}].name = \"{station_name}\";\n")
with open("output_stations.txt", "w") as f:
    f.writelines(output_lines)
