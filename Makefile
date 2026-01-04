CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = speedtest
OBJS = main.o SpeedTest.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp SpeedTest.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

SpeedTest.o: SpeedTest.cpp SpeedTest.hpp
	$(CXX) $(CXXFLAGS) -c SpeedTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
