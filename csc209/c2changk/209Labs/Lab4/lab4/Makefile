testlist : testlist.o list.o test1.o
	gcc -Wall -g -o testlist testlist.o list.o test1.o

testlist.o : testlist.c 
	gcc -Wall -g -c testlist.c

list.o : list.c list.h
	gcc -Wall -g -c list.c

test1.o : test1.c  list.h
	gcc -Wall -g -c test1.c
