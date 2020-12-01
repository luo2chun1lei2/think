# Think的总编译文件

# 事前准备
# sudo apt-get install catch
# catch: c plus plus 的单元测试工具，可以使用BDD-style的测试用例。

.PHONY: clean prepare run test

## 代码和目标名字
SRC_ROOT_DIR=./src
TARGET:=think
OUT:=./out

## 编译选项
CPP_C:=g++

CPP_FLAGS := -g
TEST_CPP_FLAGS := ${CPP_FLAGS}
LD_FLAGS := -g
TEST_LD_FLAGS := ${LD_FLAGS}

## 扩展的宏
TARGET_PATH := ${OUT}/${TARGET}
TEST_TARGET := ${TARGET}.test
TEST_TARGET_PATH := ${OUT}/${TEST_TARGET}

#TEST_SRC := $(vpath src/*.test.cpp)
SUB_DIRS = $(shell find ${SRC_ROOT_DIR} -type d)
#$(wildcard src/*.test.cpp)
TEST_SRC := $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.test.cpp))
SRC := $(filter-out ${TEST_SRC}, $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.cpp)))

OBJS := $(patsubst ${SRC_ROOT_DIR}/%.cpp,${OUT}/%.o,${SRC})
TEST_OBJS := $(patsubst ${SRC_ROOT_DIR}/%.cpp,${OUT}/%.o,${TEST_SRC})

## 规则
all:
	@echo "${SUB_DIRS} | ${SRC} -> ${OBJS} | ${TEST_SRC} -> ${TEST_OBJS}"

prepare:
	mkdir -p ${OUT}

${OUT}/%.o:${SRC_ROOT_DIR}/%.test.cpp
	mkdir -p `dirname $@`
	$(CPP_C) $(TEST_CPP_FLAGS) -c $< -o $@

${OUT}/%.o:${SRC_ROOT_DIR}/%.cpp
	mkdir -p `dirname $@`
	$(CPP_C) $(CPP_FLAGS) -c $< -o $@

build_exe: prepare ${OBJS}
	${CPP_C} ${LD_FLAGS} ${OBJS} -o ${TARGET_PATH}

build_test: build_exe prepare ${TEST_OBJS}
	${CPP_C} ${TEST_LD_FLAGS} ${TEST_OBJS} -o ${TEST_TARGET_PATH}

all: build_exe build_test

clean:
	@rm -rf ${OUT}
	
run: build_exe
	${TARGET_PATH}
	
test: build_test
	${TEST_TARGET_PATH}
