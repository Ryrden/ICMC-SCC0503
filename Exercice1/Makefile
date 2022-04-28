UTIL=Util/util.c fileHandler/fileHandler.c uspDatabase/uspDatabase.c
MAIN=main.c
BINARY=main

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

testCase 1:
	./$(BINARY) < ./Casos\ de\ Teste/1.in

clean:
	@rm *.o