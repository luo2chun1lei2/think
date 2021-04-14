# 原文链接：https://blog.csdn.net/sinat_37806635/article/details/81138771

LEX = flex
YYAC = bison
CC = gcc

all: test

test: parser.tab.o scanner.o
	$(CC) -o $@ parser.tab.o scanner.o

parser.tab.c parser.tab.h: parser.y
	$(YYAC) -vd parser.y

scanner.c: scanner.l
	$(LEX) -o $@ $<

scanner.o: scanner.c parser.tab.h

.PYHONY: clean

clean:
	-@rm parser.tab.c parser.tab.h scanner.c parser.output *.o test

# 可以在输入 test 后，输入各种C语言简单的表达式，然后看语法分析结果。
