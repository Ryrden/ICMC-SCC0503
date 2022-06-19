UTIL= bTree/bTree.c uspDatabase/uspDatabase.c Util/util.c dataHandler/dataHandler.c
MAIN=main.c
BINARY=main.out

all:
	gcc $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

test: # usar o comando da forma:$ make test case=<nº do caso que quiser>
	./$(BINARY) < ./Casos\ de\ Teste/$(case).in

testV: # usar o comando da forma:$ make testV case=<nº do caso que quiser>
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY) < ./Casos\ de\ Teste/$(case).in

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm -rf *.o *.bin *.out
