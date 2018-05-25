AddBrace : check.o main.o
	c++ -o AddBrace check.o main.o

check.o : check.cpp check.h char.h
	c++ -c check.cpp

main.o : main.cpp check.h
	c++ -c main.cpp

clean : 
	rm main.o check.o
