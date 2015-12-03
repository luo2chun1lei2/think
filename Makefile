TARGET=think

all:${TARGET}

${TARGET}:robject.o main.o 
	g++ $^ -o $@

main.o:main.cc
	g++ -c $<
	
robject.o:robject.cc robject.h
	g++ -c $<

clean:
	rm -rf *.o ${TARGET}
