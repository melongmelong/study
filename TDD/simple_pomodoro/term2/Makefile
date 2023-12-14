.PHONY: all src test clean

all: src test

test: src
	make -C test

src: 
	make -C src

clean:
	make -C test clean
	make -C src clean
