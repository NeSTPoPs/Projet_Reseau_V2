#Makefile pour Projet TEST

main: main.o Trame.o IpFrame.o fonctionsMaths.o Data.o
	g++ -o main main.o Trame.o IpFrame.o fonctionsMaths.o Data.o

Trame.o: Trame.cpp Trame.h fonctionsMaths.h IpFrame.h
	g++ -Wall -c Trame.cpp

IpFrame.o: IpFrame.cpp IpFrame.h Data.h
	g++ -Wall -c IpFrame.cpp

fonctionsMaths.o: fonctionsMaths.cpp fonctionsMaths.h
	g++ -Wall -c fonctionsMaths.cpp

Data.o:	Data.cpp Data.h fonctionsMaths.h
	g++ -Wall -c Data.cpp
clean: 
	rm -f main Trame.o functionsMaths.o IpFrame.o 



	
