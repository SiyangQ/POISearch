all: map1 map2

map1: map1.o structureCLUE.o KDTree.o list.o mathFunctions.o print.o
	gcc -Wall -std=c99 -o map1 map1.o structureCLUE.o KDTree.o list.o mathFunctions.o print.o -lm

map2: map2.o structureCLUE.o KDTree.o list.o mathFunctions.o print.o
	gcc -Wall -std=c99 -o map2 map2.o structureCLUE.o KDTree.o list.o mathFunctions.o print.o -lm

map1.o: map1.c structureCLUE.h KDTree.h
	gcc -Wall -std=c99 -o map1.o -c map1.c -g

map2.o: map2.c
	gcc -Wall -std=c99 -o map2.o -c map2.c -g

list.o: list.c list.h
	gcc -Wall -std=c99 -o list.o -c list.c -g

print.o: print.c print.h
	gcc -Wall -std=c99 -o print.o -c print.c -g

structureCLUE.o: structureCLUE.c structureCLUE.h
	gcc -Wall -std=c99 -o structureCLUE.o -c structureCLUE.c -g

KDTree.o: KDTree.c KDTree.h
	gcc -Wall -std=c99 -o KDTree.o -c KDTree.c -g -lm

mathFunctions.o: mathFunctions.c mathFunctions.h
	gcc -Wall -std=c99 -o mathFunctions.o -c mathFunctions.c -g -lm

clean:
	rm -f map1 map2 *.o *.txt *.csv