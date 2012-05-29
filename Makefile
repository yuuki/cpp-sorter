CXX = g++-4.7
CXXFLAGS = -O2 -Wall -Wextra -std=c++11
TARGET = sorter
OBJS	= main.o
LDFLAGS=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(XX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(XX) $(CXXFLAGS) -o $@ -c $^

clean:
	$(RM) $(OBJS)
