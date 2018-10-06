P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h Table.hpp
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h Table.hpp
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch


runTest: P1.out
	clear;
	./P1.out testfile.ss

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf missamoreP1
	mkdir missamoreP1
	cp Project1.cpp missamoreP1
	cp LexicalAnalyzer.h missamoreP1
	cp LexicalAnalyzer.cpp missamoreP1
	cp SyntacticalAnalyzer.h missamoreP1
	cp SyntacticalAnalyzer.cpp missamoreP1
	cp makefile missamoreP1
	cp README.txt missamoreP1
	tar cfvz missamoreP1.tgz missamoreP1
	cp missamoreP1.tgz ~tiawatts/cs460drop
