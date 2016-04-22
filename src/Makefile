TARGET=think
CC=g++
CFLAGS= --std=c++11 -g
LDFLAGS= -g

all:${TARGET}

${TARGET}:main.o element.o
	${CC} ${LDFLAGS} $^ -o $@

main.o:main.cc
	${CC} ${CFLAGS} -c $<

element.o:element.cc element.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}

run:
	./think

debug:
	gdb ./think