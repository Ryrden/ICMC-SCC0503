UTIL= Util/util.c list/list.c primaryIndex/primaryIndex.c dataHandler/dataHandler.c uspDatabase/uspDatabase.c
MAIN=main.c
BINARY=main
NAME=Exercicio2

all:
	gcc -Wall -g $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip $(MAIN) Util/ list/ primaryIndex/ dataHandler/ uspDatabase/

clean:
	@rm *.o