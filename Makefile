.PHONY: doc clean dirs

SRC=src
TEST=test
OBJ=obj
BIN=bin
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -lstdc++
CVCONFIG=`pkg-config --libs opencv4` `pkg-config --cflags opencv4` -lstdc++
GTEST=-lgtest -lgtest_main -pthread
CLANG=clang++ -Wall

all: dirs Darknet $(BIN)/test

Darknet: $(SRC)/darknet.cpp
	$(CLANG) $^ -o $@ $(CFLAGS)

$(BIN)/test: $(TEST)/test.cpp
	$(CLANG) $^ -o $@ $(CFLAGS) $(GTEST)

dirs:
	mkdir -p $(SRC) $(OBJ) $(TEST) $(BIN)

clean:
	rm -rf Darknet $(OBJ) $(BIN)

doc:
	doxygen Doxygen

run:
	./HyperMedical

stat:
	wc src/*
