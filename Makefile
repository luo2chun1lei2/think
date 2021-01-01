# Think的总编译文件

# 事前准备
# sudo apt-get install catch uuid-dev libgraphviz-dev
# catch: c plus plus 的单元测试工具，可以使用BDD-style的测试用例。

.PHONY: clean prepare run test format

## 代码和目标名字
SRC_ROOT_DIR=./src
TARGET:=think
OUT:=./out
INCLUDE_DIR :=

## 编译选项
CPP_C:=g++

CPP_FLAGS := `pkg-config libgvc --cflags` -Wall -g
TEST_CPP_FLAGS := ${CPP_FLAGS}
LD_FLAGS := -luuid `pkg-config libgvc --libs` -g
TEST_LD_FLAGS := ${LD_FLAGS}

## 扩展的宏
TARGET_PATH := ${OUT}/${TARGET}
TEST_TARGET := ${TARGET}.test
TEST_TARGET_PATH := ${OUT}/${TEST_TARGET}

SUB_DIRS = $(shell find ${SRC_ROOT_DIR} -type d)

TEST_SRC := $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.test.cpp))
SRC := $(filter-out ${TEST_SRC}, $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.cpp)))
HEADS := $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.hpp))

INCLUDE_DIR += $(patsubst %,-I%,${SUB_DIRS})

OBJS := $(patsubst ${SRC_ROOT_DIR}/%.cpp,${OUT}/%.o,${SRC})
TEST_OBJS := $(patsubst ${SRC_ROOT_DIR}/%.cpp,${OUT}/%.o,${TEST_SRC})

## 规则
all:
	@echo "${SUB_DIRS} | ${INCLUDE_DIR} | ${SRC} -> ${OBJS} | ${TEST_SRC} -> ${TEST_OBJS}"

prepare:
	@mkdir -p ${OUT}

${OUT}/%.test.o:${SRC_ROOT_DIR}/%.test.cpp ${HEADS}
	mkdir -p `dirname $@`
	$(CPP_C) $(INCLUDE_DIR) $(TEST_CPP_FLAGS) -c $< -o $@

${OUT}/%.o:${SRC_ROOT_DIR}/%.cpp ${HEADS}
	mkdir -p `dirname $@`
	$(CPP_C) $(INCLUDE_DIR) $(CPP_FLAGS) -c $< -o $@

build_exe: prepare ${OBJS}
	${CPP_C} ${OBJS} ${LD_FLAGS} -o ${TARGET_PATH}

build_test: build_exe prepare ${TEST_OBJS} $(filter-out ${OUT}/Main.o, ${OBJS})
	${CPP_C} ${TEST_OBJS} $(filter-out ${OUT}/Main.o, ${OBJS}) ${TEST_LD_FLAGS} -o ${TEST_TARGET_PATH}

all: build_test

clean:
	@rm -rf ${OUT}
	
run: build_exe
	@${TARGET_PATH} ${ARGS}

test: build_test
	@${TEST_TARGET_PATH}${ARGS}

# 不运行可以阻塞的测试项目	
auto_test: build_test
	@${TEST_TARGET_PATH} ~[block] ${ARGS}

# 使用clang-format，配置参数在 .clang-format文件中。
# ident工具对于c++语法解析的不正确。
format:
	@clang-format -i ${SRC} ${TEST_SRC}
