CXX = g++-4.7
CXXFLAGS = -O2 -Wall -Wextra -std=c++11
TARGET = sorter
OBJS	= main.o
TOBJS = test.o
BOBJS = bench.o
LDFLAGS=

all: $(TARGET)

test: test
	$(CXX) $(CXXFLAGS) $(TOBJS) -o $@
	./test

bench: bench
	$(CXX) $(CXXFLAGS) $(BOBJS) -o $@
	./bench

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $^

clean:
	$(RM) $(TARGET) $(OBJS)
