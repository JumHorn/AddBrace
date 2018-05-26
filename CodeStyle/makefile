AddBrace : check.o main.o
	g++ -o AddBrace check.o main.o

check.o : check.cpp check.h char.h
	g++ -c check.cpp

main.o : main.cpp check.h
	g++ -c main.cpp

clean : 
	rm main.o check.o
