#!/bin/bash

test_directory="./test"
time_command="/usr/bin/time -p -f %e"

if [ ! -d $test_directory ]; then
  mkdir $test_directory
fi

rm -f $test_directory/*

for percent in `seq 5 5 100`; do
  echo Running test with density $percent.
  ./graph_generator $percent > $test_directory/graph$percent.txt

  printf $percent\  >> $test_directory/prim.time
  $time_command ./prim \
    < $test_directory/graph$percent.txt \
    > $test_directory/prim$percent.out 2>> \
    $test_directory/prim.time

  printf $percent\  >> $test_directory/kruskal.time
  $time_command ./kruskal \
    < $test_directory/graph$percent.txt \
    > $test_directory/kruskal$percent.out 2>> \
    $test_directory/kruskal.time

  printf $percent\  >> $test_directory/boruvka.time
  $time_command ./boruvka \
    < $test_directory/graph$percent.txt > \
    $test_directory/boruvka$percent.out 2>> \
    $test_directory/boruvka.time

  if ! cmp --silent $test_directory/prim$percent.out \
    $test_directory/kruskal$percent.out; then
    echo "Prim's and Kruskal's answers don't match"
  fi
  if ! cmp --silent $test_directory/prim$percent.out \
    $test_directory/boruvka$percent.out; then
    echo "Prim's and Borůvka's answers don't match"
  fi
done

