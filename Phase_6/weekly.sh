#!/bin/sh
echo "Weekly Script"
for k in 1 2 3 4 5
do
  echo "Running Day $k:"
  ./daily.sh
done
