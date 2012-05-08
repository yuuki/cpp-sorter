CC = /usr/local/bin/g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++11
TARGET = sorter
OBJS	= main.o
LDFLAGS=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $^

clean:
	$(RM) $(OBJS)
