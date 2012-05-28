CC = /usr/local/bin/g++-4.7
CXXFLAGS = -O2 -Wall -Wextra -std=c++11
TARGET = sorter
OBJS	= main.o
LDFLAGS=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) -o $@ -c $^

clean:
	$(RM) $(OBJS)
