CPPFLAGS=-std=c++11

all: graph_generator prim kruskal

graph_generator: graph_generator.cpp
prim: prim.cpp
kruskal: kruskal.cpp

test: all
	./graph_generator 20 > graph.txt
	./prim < graph.txt > prim.out
	./kruskal < graph.txt > kruskal.out

clean:
	$(RM) prim graph_generator
