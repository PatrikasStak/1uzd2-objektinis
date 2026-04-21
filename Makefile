CXX := g++
OPT ?= -O2
CXXFLAGS := $(OPT) -std=c++14 -Wall -Wextra -pedantic

SRC := main.cpp func.cpp Studentas.cpp
OBJ := $(SRC:.cpp=.o)
BIN := main
TEST_BIN := studentas_test

all: $(BIN)
test: $(TEST_BIN)

$(TEST_BIN): studentas_test.cpp Studentas.cpp
	$(CXX) $(CXXFLAGS) -o $@ studentas_test.cpp Studentas.cpp

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
	rm -f $(OBJ) $(BIN) $(TEST_BIN)

.PHONY: all clean o1 o2 o3 test
