CXX := g++
OPT ?= -O2
CXXFLAGS := $(OPT) -std=c++14 -Wall -Wextra -pedantic

SRC := main.cpp func.cpp Studentas.cpp
OBJ := $(SRC:.cpp=.o)
BIN := main
TEST_BIN      := studentas_test
VECTOR_TEST   := vector_test
BENCH_BIN     := benchmark
REALLOC_BIN   := realloc_benchmark

all: $(BIN)

test: $(TEST_BIN) $(VECTOR_TEST)
	./$(TEST_BIN)
	./$(VECTOR_TEST)

$(TEST_BIN): studentas_test.cpp Studentas.cpp catch.hpp
	$(CXX) $(OPT) -std=c++14 -o $@ studentas_test.cpp Studentas.cpp

$(VECTOR_TEST): vector_test.cpp Vector.h catch.hpp
	$(CXX) $(OPT) -std=c++14 -o $@ vector_test.cpp

$(BENCH_BIN): benchmark.cpp Vector.h
	$(CXX) -O2 -std=c++14 -o $@ benchmark.cpp

$(REALLOC_BIN): realloc_benchmark.cpp Vector.h
	$(CXX) -O2 -std=c++14 -o $@ realloc_benchmark.cpp

docs:
	doxygen Doxyfile

o1:
	$(MAKE) clean
	$(MAKE) OPT=-O1 all

o2:
	$(MAKE) clean
	$(MAKE) OPT=-O2 all

o3:
	$(MAKE) clean
	$(MAKE) OPT=-O3 all

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(BIN) $(TEST_BIN) $(VECTOR_TEST) $(BENCH_BIN) $(REALLOC_BIN)

.PHONY: all clean o1 o2 o3 test docs
