.PHONY: doc clean dirs test

SRC=src
TEST=test
OBJ=obj
BIN=bin
CFLAGS=-Wall -Wno-unused-result -Wno-unused-function -Wno-unknown-pragmas -Wno-unused-command-line-argument -Wfatal-errors -fPIC -lstdc++
CVCONFIG=`pkg-config --libs opencv4` `pkg-config --cflags opencv4`
GTEST=-lgtest -lgtest_main -pthread
CLANG=clang++ -Wall -std=c++11

all: dirs Darknet $(BIN)/test

Darknet: $(SRC)/darknet.cpp \
	$(OBJ)/network.o
	$(CLANG) $^ -o $@ $(CFLAGS)

$(BIN)/test: $(TEST)/test.cpp \
	$(OBJ)/network.o
	$(CLANG) $^ -o $@ $(CFLAGS) $(GTEST)

$(OBJ)/network.o: $(SRC)/network.cpp
	$(CLANG) -c $< -o $@ $(CFLAGS)

dirs:
	mkdir -p $(SRC) $(OBJ) $(TEST) $(BIN)

clean:
	rm -rf Darknet $(OBJ) $(BIN)

doc:
	doxygen Doxygen

test:
	./bin/test

run:
	./Darknet predict ff

stat:
	wc src/*
