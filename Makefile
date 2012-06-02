CXX = g++-4.7
CXXFLAGS = -O2 -Wall -Wextra -std=c++11
TARGET = sorter
OBJS	= main.o
TOBJS = test.o
BOBJS = bench.o
LDFLAGS=

LIB_BOOST_TEST:=-lboost_unit_test_framework-mt

all: $(TARGET)

test: test
	$(CXX) $(CXXFLAGS) $(TOBJS) -o $@
	./test

bench: bench.cpp sorter.hpp
	$(CXX) $(CXXFLAGS) bench.cpp -o $@
	./bench

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $^

clean:
	$(RM) $(TARGET) $(OBJS)
