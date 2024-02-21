#!/bin/bash

run_script="/home/cs/hlds/run.sh"
hlds_directory="/home/cs/hlds/"

cd "$hlds_directory"

for port in {27016..27079}; do
    echo "Running $run_script for port $port in the background..."
    nohup sudo "$run_script" "$port" > /dev/null 2>&1 &
done

