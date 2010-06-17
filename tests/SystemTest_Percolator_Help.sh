#!/bin/bash

cd $1

# We are at percolator 'bin' folder now.

run_command=$(percolator --help 2>&1)

if [ $? -eq 0 ]; then
  echo "$0 finished successfully!"
  exit 0
else
  echo "ERROR: $0 exited with an error code."
  exit 1
fi
