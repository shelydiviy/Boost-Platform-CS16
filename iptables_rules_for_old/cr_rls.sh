#!/bin/bash

# Specify the destination IP address
destination_ip="145.239.138.255"

# Specify the starting and ending ports
start_port=27016
end_port=27079

# Loop through the port range and create DNAT rules
for ((port = start_port; port <= end_port; port++)); do
    iptables -t nat -A PREROUTING -p udp --dport $port -j DNAT --to-destination "$destination_ip:$((port + 200))"
    iptables -t nat -A POSTROUTING -p udp -s "$destination_ip" --sport "$((port + 200))" -j SNAT --to-source "$destination_ip:$port"
done
