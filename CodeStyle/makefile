AddBrace : formatter.o main.o style.o statistics.o
	g++ -o AddBrace formatter.o main.o style.o statistics.o

style.o : style.cpp style.h ignore.hpp char.h
	g++ -c style.cpp

formatter.o : formatter.cpp formatter.h ignore.hpp char.h
	g++ -c formatter.cpp

statistics.o : statistics.cpp statistics.h ignore.hpp char.h
	g++ -c statistics.cpp

main.o : main.cpp formatter.h style.h
	g++ -c main.cpp

clean : 
	rm main.o formatter.o style.o statistics.o
