CFLAGS=-std=c11 -g -static

9cc: 9cc.c

test: 9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp*

dockerit:
	docker run -it --rm -v .:/9cc -w /9cc --name 9cc compilerbook /bin/bash

.PHONY: test clean
