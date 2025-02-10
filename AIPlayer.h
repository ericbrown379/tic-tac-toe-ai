#pragma once
#include "Player.h"
#include <map>
#include <vector>
#include <string>

struct MoveValue {
    int position;
    double value;
};

class AIPlayer : public Player {
private:
    std::map<std::string, std::vector<MoveValue>> moveMemory;
    double learningRate;
    std::string apiKey;

    std::string makeOpenAIRequest(const std::string& board_state);
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

public:
    AIPlayer(char marker, const std::string& key);
    int getMove(const Board& board) override;
    void updateMoveValue(const std::string& state, int move, bool won);
    void saveToFile() const;
    void loadFromFile();
};