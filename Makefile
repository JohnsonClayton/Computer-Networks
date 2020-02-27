makefile:

clean: clay_copy
	rm clay_copy

copier: clay_copy.c
	gcc -g clay_copy.c -o clay_copy
