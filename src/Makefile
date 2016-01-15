TARGET=think
CC=g++
CFLAGS= --std=c++11 -g
LDFLAGS= -g

all:${TARGET}

${TARGET}:subject_observer.o rdata.o robject.o main.o test1.cc test2.cc
	${CC} ${LDFLAGS} $^ -o $@

main.o:main.cc
	${CC} ${CFLAGS} -c $<

robject.o:robject.cc robject.h
	${CC} ${CFLAGS} -c $<

subject_observer.o:subject_observer.cc subject_observer.h
	${CC} ${CFLAGS} -c $<

rdata.o:rdata.cc rdata.h
	${CC} ${CFLAGS} -c $<

test1.o:test1.cc
	${CC} ${CFLAGS} -c $<

test2.o:test2.cc
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}

run:
	./think
