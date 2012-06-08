CXX = g++-4.7
CXXFLAGS = -O2 -Wall -Wextra -std=c++11 -I/usr/local/include -L/usr/local/lib -ltbb
TARGET = sort
OBJS	= main.o
LDFLAGS=

LIB_BOOST_TEST:=-lboost_unit_test_framework-mt

all: $(TARGET)

test: test.cpp sorter.hpp
	$(CXX) $(CXXFLAGS) $(LIB_BOOST_TEST) test.cpp -o $@
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
