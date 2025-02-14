CXX = g++
CXXFLAGS = -std=c++17 -Wall -I"C:/path/to/SDL/include"
LDFLAGS = -L"C:/path/to/SDL/lib" -lSDL2

SRCS = main.cpp Game.cpp Board.cpp HumanPlayer.cpp AIPlayer.cpp SDLGUI.cpp
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