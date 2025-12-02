CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = scheduler
SRC = main.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) sample_input.txt

clean:
	rm -f $(TARGET)
