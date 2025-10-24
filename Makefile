CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -I./source -I./source/coisas

SRCS := $(shell find source -name '*.cpp')
OBJS := $(SRCS:.cpp=.o)

TARGET := bin/snaze

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	@echo "Running $(TARGET)"
	@$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
