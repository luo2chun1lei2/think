TARGET=think
CC=g++
#CFLAGS= -g --std=c++11 `pkg-config gtkmm-3.0 --cflags`
CFLAGS= -g `pkg-config gtkmm-3.0 --cflags`
LDFLAGS= -g `pkg-config gtkmm-3.0 --libs`

all:${TARGET}

# LDFLAGS 必须放在后面。
${TARGET}:main.o element.o app.o
	${CC} $^ -o $@ ${LDFLAGS}

main.o:main.cpp
	${CC} ${CFLAGS} -c $<

element.o:element.cpp element.h
	${CC} ${CFLAGS} -c $<

app.o:app.cpp app.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${TARGET}

run:
	./think

debug:
	gdb ./think
