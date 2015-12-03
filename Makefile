all:main.o
	g++ $^

main.o:main.cc
	g++ -c $^
	

clean:
	rm -rf *.o a.out
