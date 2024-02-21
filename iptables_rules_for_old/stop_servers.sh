#!/bin/bash

# Terminate processes by matching the command line
sudo pkill -f "hlds_linux -console -game cstrike"
sudo pkill -f "/home/cs/hlds/hlds_run -console -game cstrike"

echo "Server processes terminated."

