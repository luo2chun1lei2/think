.PHONY: all clean

all:
	make -C src
	make -C view

clean:
	make clean -C src

run:
	make run -C src
