calc: clean
	bison -d calc.y
	flex  calc.lex
	cp calc.tab.c calc.tab.cpp
	gcc lex.yy.c   -c 
	g++ calc.tab.cpp -c -std=c++11
	g++ parser_utils.cpp -c -std=c++11
	ar rc parser.a lex.yy.o calc.tab.o parser_utils.o 
	
clean:
	rm -f lex.yy.c calc.tab.c  calc.tab.cpp  calc.tab.h lex.yy.c parser.a

# -lfl -lm -o calc
	
 # calc.y calc.lex
 
#  -o calc.lex.c