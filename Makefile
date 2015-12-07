TARGET=think
CC=g++
CFLAGS= --std=c++11
LDFLAGS=

all:${TARGET}

${TARGET}:robject.o main.o 
	${CC} ${LDFLAGS} $^ -o $@

main.o:main.cc
	${CC} ${CFLAGS} -c $<
	
robject.o:robject.cc robject.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}
