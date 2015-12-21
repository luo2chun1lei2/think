TARGET=think
CC=g++
CFLAGS= --std=c++11 -g
LDFLAGS= -g

all:${TARGET}

${TARGET}:subject_observer.o rdata.o robject.o main.o 
	${CC} ${LDFLAGS} $^ -o $@

main.o:main.cc
	${CC} ${CFLAGS} -c $<

robject.o:robject.cc robject.h
	${CC} ${CFLAGS} -c $<

subject_observer.o:subject_observer.cc subject_observer.h
	${CC} ${CFLAGS} -c $<

rdata.o:rdata.cc rdata.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}

run:
	./think
