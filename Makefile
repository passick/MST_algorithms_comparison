CPPFLAGS=-std=c++11

all: graph_generator prim kruskal boruvka

graph_generator: graph_generator.cpp
prim: prim.cpp
kruskal: kruskal.cpp
boruvka: boruvka.cpp

test: all
	/bin/bash ./tester.sh

clean:
	$(RM) prim graph_generator kruskal boruvka ./test/*
