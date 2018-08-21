AddBrace : formatter.o main.o
	g++ -o AddBrace formatter.o main.o

formatter.o : formatter.cpp
	g++ -c formatter.cpp

main.o : main.cpp
	g++ -c main.cpp

clean : 
	rm main.o formatter.o
