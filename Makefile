CXX = g++
CXXFLAGS = -std=c++17 -Wall
# Use the correct path for nlohmann-json
CXXFLAGS += -I/opt/homebrew/opt/nlohmann-json/include
LDFLAGS = -lcurl -L/opt/homebrew/lib

SRCS = main.cpp Game.cpp Board.cpp HumanPlayer.cpp AIPlayer.cpp Config.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = tictactoe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)