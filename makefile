CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = musicplayer.cpp record.cpp 
OBJS = $(SRCS:.cpp=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

musicplayer.o: musicplayer.cpp record.h
	$(CXX) $(CXXFLAGS) -c musicplayer.cpp

record.o: record.cpp record.h 
	$(CXX) $(CXXFLAGS) -c record.cpp

clean:
	rm -f $(OBJS) $(TARGET)
