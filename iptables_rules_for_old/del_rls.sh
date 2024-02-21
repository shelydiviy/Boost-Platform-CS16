#!/bin/bash

# Specify the destination IP address
destination_ip="145.239.138.255"

# Specify the starting and ending ports
start_port=27016
end_port=27079

# Loop through the port range and delete DNAT rules
for ((port = start_port; port <= end_port; port++)); do
    iptables -t nat -D PREROUTING -p udp --dport $port -j DNAT --to-destination "$destination_ip:$((port + 200))"
    iptables -t nat -D POSTROUTING -p udp -s "$destination_ip" --sport "$((port + 200))" -j SNAT --to-source "$destination_ip:$port"
done

