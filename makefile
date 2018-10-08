files = Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp Table.hpp makefile README.txt
output_files = *.lst *.p1

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
	rm -f *.o P1.out 
	rm -rf TeamfP1
	rm -f TeamfP1.tgz
	rm -rf $(output_files)

runTest: P1.out
	clear;
	./P1.out testfile.ss

submission : $(files)
	rm -rf TeamfP1
	mkdir TeamfP1
	cp Project1.cpp TeamfP1
	cp LexicalAnalyzer.h TeamfP1
	cp LexicalAnalyzer.cpp TeamfP1
	cp SyntacticalAnalyzer.h TeamfP1
	cp SyntacticalAnalyzer.cpp TeamfP1
	cp Table.hpp TeamfP1
	cp makefile TeamfP1
	cp README.txt TeamfP1

test: submission SetLimits.h SetLimits.cpp *.ss
	cp SetLimits.h TeamfP1
	cp SetLimits.cpp TeamfP1
	cp *.ss TeamfP1

	
submit : submission
	tar cfvz TeamfP1.tgz TeamfP1
	cp TeamfP1.tgz ~tiawatts/cs460drop

