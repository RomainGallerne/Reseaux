all: TP4
sock.o: sock.cc sock.h
	g++ -c sock.cc
sockdist.o: sockdist.cc sockdist.h
	g++ -c sockdist.cc

ClientTCP: ClientTCP.cpp sock.o sockdist.o
g++ -o ClientTCP  ClientTCP.cpp sock.o sockdist.o

ServeurTCP: ServeurTCP.cpp sock.o sockdist.o
g++ -o ServeurTCP ServeurTCP.cpp sock.o sockdist.o