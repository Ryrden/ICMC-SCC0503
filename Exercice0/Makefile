UTIL= list/list.c uspDatabase/uspDatabase.c Util/util.c
MAIN=main.c
BINARY=main
NAME=Exercicio0
all:
	gcc -Wall -g $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip main.c list/ uspDatabase/ Util Makefile

clean:
	@rm *.o