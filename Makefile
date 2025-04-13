CXX=g++

CXXFLAGS=-Wall -g -Iinclude

ifeq ($(OS),Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=%.o)

TARGET = render

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) *.o *.exe
