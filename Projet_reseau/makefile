#Makefile pour Projet TEST

main: main.o Trame.o IpFrame.o fonctionsMaths.o Data.o IcmpFrame.o ArpFrame.o
	g++ -o main main.o Trame.o IpFrame.o fonctionsMaths.o Data.o IcmpFrame.o ArpFrame.o

Trame.o: Trame.cpp Trame.h fonctionsMaths.h IpFrame.h
	g++ -Wall -c Trame.cpp

IpFrame.o: IpFrame.cpp IpFrame.h Data.h IcmpFrame.h
	g++ -Wall -c IpFrame.cpp

fonctionsMaths.o: fonctionsMaths.cpp fonctionsMaths.h
	g++ -Wall -c fonctionsMaths.cpp

Data.o:	Data.cpp Data.h fonctionsMaths.h
	g++ -Wall -c Data.cpp

ArpFrame.o:	ArpFrame.cpp ArpFrame.h Data.h
		g++ -Wall -c ArpFrame.cpp

IcmpFrame.o:	IcmpFrame.cpp IcmpFrame.h Data.h
				g++ -Wall -c IcmpFrame.cpp

clean:
	rm -f main *.o
