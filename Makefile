CFLAGS=-std=c11 -g -static

9cc: 9cc.c

test: 9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp*

dockerit:
	docker run --rm -it -v .:/9cc -w /9cc compilerbook

.PHONY: test clean
