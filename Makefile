CPPFLAGS=-std=c++11

all: graph_generator prim kruskal boruvka

graph_generator: graph_generator.cpp
prim: prim.cpp
kruskal: kruskal.cpp
boruvka: boruvka.cpp

test: all
	/bin/bash ./tester.sh

plot: analysis/plot.tex
analysis/plot.tex:
	if [ ! -d "./analysis" ]; then mkdir ./analysis; fi
	gnuplot ./gnuplot.script

analysis: analysis/analysis.pdf
	mv ./analysis/analysis.pdf ./
analysis/analysis.pdf: analysis.tex analysis/plot.tex
	pdflatex -output-directory=./analysis ./analysis.tex
	$(RM) texput.log

clean:
	$(RM) prim graph_generator kruskal boruvka ./test/* \
	  ./analysis/* ./analysis.pdf
