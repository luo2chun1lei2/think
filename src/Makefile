USE_CLANG=0

ifeq (${USE_CLANG}, 1)
  CC=/home/luocl/test/sdk/toolchains/clang/bin/clang
  CPP=/home/luocl/test/sdk/toolchains/clang/bin/clang++
else
  CC=gcc
  CPP=g++
endif

TARGET=a.out
SRCS=main.cc

CFLAGS=
CPP_FLAGS= ${CFLAGS}
C_FLAGS= ${CFLAGS}

OBJS=$(patsubst %,%.o,${SRCS})
all: ${OBJS}
	${CPP} $^ -o ${TARGET}

C_OBJS=$(filter %.c.o, ${OBJS})
${C_OBJS}: %.c.o: %.c
	${CC} ${C_FLAGS} -c $< -o $@

CPP_OBJS=$(filter %.cc.o, ${OBJS})
${CPP_OBJS}: %.cc.o: %.cc
	${CPP} ${CPP_FLAGS} -c $< -o $@

run:
	@./${TARGET}

clean:
	rm -rf *.o ${TARGET}
