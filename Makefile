CPPFLAGS=-std=c++11

all: graph_generator prim

graph_generator: graph_generator.cpp
prim: prim.cpp

clean:
	$(RM) prim graph_generator
