CXX = g++
CXXFLAGS = -Iinclude -std=c++11

SRC = $(wildcard src/*.cpp src/auth/*.cpp src/recipe/*.cpp src/utils/*.cpp)

TARGET = my_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)
