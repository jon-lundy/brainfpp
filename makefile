all: brainfpp

brainfpp: main.o parser.o datanode.o inputnode.o loopnode.o outputnode.o pointernode.o programnode.o abstractnode.o programstate.o
	g++ main.o parser.o datanode.o inputnode.o loopnode.o outputnode.o pointernode.o programnode.o abstractnode.o programstate.o -o brainfpp

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

datanode.o: datanode.cpp
	g++ -c datanode.cpp

inputnode.o: inputnode.cpp
	g++ -c inputnode.cpp

loopnode.o: loopnode.cpp
	g++ -c loopnode.cpp

outputnode.o: outputnode.cpp
	g++ -c outputnode.cpp

pointernode.o: pointernode.cpp
	g++ -c pointernode.cpp

programnode.o: programnode.cpp
	g++ -c programnode.cpp

abstractnode.o: abstractnode.cpp
	g++ -c abstractnode.cpp

programstate.o: programstate.cpp
	g++ -c programstate.cpp

clean:
	rm -rf *o brainfpp
