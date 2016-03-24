TARGET=think
CC=g++
CFLAGS= --std=c++11 -g
LDFLAGS= -g

all:${TARGET}

${TARGET}:main.o object.o
	${CC} ${LDFLAGS} $^ -o $@

main.o:main.cc
	${CC} ${CFLAGS} -c $<

object.o:object.cc object.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}

run:
	./think
