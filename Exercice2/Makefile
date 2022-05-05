UTIL=Util/util.c fileHandler/fileHandler.c dataHandler/dataHandler uspDatabase/uspDatabase.c
MAIN=main.c
BINARY=main
NAME=Exercicio1

all:
	gcc -Wall -g $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip $(MAIN) fileHandler/ uspDatabase/ Util Makefile

clean:
	@rm *.o