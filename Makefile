CXX = g++
CXXFLAGS = -Iinclude -std=c++17

SRC = $(wildcard src/*.cpp src/auth/*.cpp src/recipe/*.cpp src/utils/*.cpp)

TARGET = food-note

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)

