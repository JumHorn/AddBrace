AddBrace : formatter.o main.o
	g++ -o AddBrace formatter.o main.o

formatter.o : formatter.cpp formatter.h char.h
	g++ -c formatter.cpp

main.o : main.cpp formatter.h
	g++ -c main.cpp

clean : 
	rm main.o formatter.o
