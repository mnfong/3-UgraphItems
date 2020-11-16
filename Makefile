run: main.o  ugraph.o priorityqueue.o
	g++ -o run main.o  ugraph.o priorityqueue.o 
priorityqueue.o: priorityqueue.cpp priorityqueue.h item.h
	g++ -c -Wall -pedantic -g -std=c++11 priorityqueue.cpp
ugraph.o: ugraph.cpp ugraph.h  timestamp.h priorityqueue.h
	g++ -c -Wall -pedantic -g -std=c++11 ugraph.cpp
main.o: main.cpp  ugraph.h priorityqueue.h
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o ugraph.o priorityqueue.o run
