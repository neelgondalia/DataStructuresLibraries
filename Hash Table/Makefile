CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g  

test: makebin src/*.c
	$(CC) $(CFLAGS) src/*.c -Iinclude -o bin/test

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*

makebin:
	mkdir -p bin