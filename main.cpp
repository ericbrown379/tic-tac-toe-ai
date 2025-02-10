#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Config.h"

using namespace std;

using json = nlohmann::json;

// Forward declare the struct first
// struct MoveValue {
//     int position;
//     double value;
// };

// Forward declare the class before any functions that use it
class LearningAI {
private:
    std::map<std::string, std::vector<MoveValue> > moveMemory;
    double learningRate;

public:
    LearningAI() : learningRate(0.1) {}

    void updateMoveValue(std::string state, int move, bool won);
    int getBestMove(char* spaces);
};

class OpenAIPlayer {
private:
    std::string api_key;
    CURL *curl;
    
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string makeOpenAIRequest(const std::string& board_state) {
        std::string response;
        
        // Prepare the API request
        std::string prompt = "You are playing Tic-Tac-Toe. Here's the current board state (spaces are empty, X is player, O is you):\n";
        prompt += board_state;
        prompt += "\nWhat is your next move? Respond with just a number 1-9 representing your chosen position.";

        json request = {
            {"model", "gpt-3.5-turbo"},
            {"messages", {{
                {"role", "user"},
                {"content", prompt}
            }}}
        };

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.dump().c_str());

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headers);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "5"; // Default move if API fails
        }

        // Parse response
        json response_json = json::parse(response);
        std::string move = response_json["choices"][0]["message"]["content"];
        return move;
    }

public:
    OpenAIPlayer(const std::string& key) : api_key(key) {
        curl = curl_easy_init();
        if(!curl) {
            throw std::runtime_error("Failed to initialize CURL");
        }
    }

    ~OpenAIPlayer() {
        if(curl) curl_easy_cleanup(curl);
    }

    int getMove(char* spaces) {
        // Convert board to string representation
        std::string board_state;
        for(int i = 0; i < 9; i++) {
            board_state += spaces[i];
            if(i % 3 == 2) board_state += "\n";
        }

        // Get move from OpenAI
        std::string move_str = makeOpenAIRequest(board_state);
        int move = std::stoi(move_str);
        
        // Convert to 0-based index
        return move - 1;
    }
};

// Now we can declare these functions
void drawboard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer, OpenAIPlayer& ai);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);
string getBoardState(char *spaces);

int main() {
    try {
        // Load environment variables
        Config::init();
        
        // Create players with API key from config
        Player* human = new HumanPlayer('X', "Player");
        Player* ai = new AIPlayer('O', Config::getApiKey());
        
        char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        OpenAIPlayer openAIPlayer(Config::getApiKey());

        while (true) {
            drawboard(spaces);
            playerMove(spaces, 'X');
            drawboard(spaces);
            if (checkWinner(spaces, 'X', 'O') || checkTie(spaces)) break;

            computerMove(spaces, 'O', openAIPlayer);
            drawboard(spaces);
            if (checkWinner(spaces, 'X', 'O') || checkTie(spaces)) break;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

void drawboard(char *spaces)
{
    cout << "     |     |     \n";
    cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  \n";
    cout << "     |     |     \n";
}

void playerMove(char *spaces, char player) {
    int num;
    do {
        cout << "Enter a spot to place a marker (1-9): ";
        cin >> num;
        
        if(num < 1 || num > 9) {
            cout << "Invalid number must be 1-9" << endl;
            continue;
        }
        
        num--; // Convert to 0-based index
        if(spaces[num] == ' ') {
            spaces[num] = player;
            break;
        } else {
            cout << "That spot is taken!" << endl;
        }
    } while(true);
}

void computerMove(char *spaces, char computer, OpenAIPlayer& ai) {
    int move;
    do {
        move = ai.getMove(spaces);
        if(move >= 0 && move < 9 && spaces[move] == ' ') {
            spaces[move] = computer;
            break;
        }
    } while(true);
}

bool checkWinner(char *spaces, char player, char computer){
    // Horizontal
    if((spaces[0] != ' ') &&  (spaces[0] == spaces[1]) && (spaces[1] == spaces[2])){
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    else if((spaces[3] != ' ') &&  (spaces[3] == spaces[4]) && (spaces[4] == spaces[5])){
        spaces[3] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    } 
    else if((spaces[6] != ' ') &&  (spaces[6] == spaces[7]) && (spaces[7] == spaces[8])){
        spaces[6] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    } 
    // Vertical
    else if((spaces[0] != ' ') &&  (spaces[0] == spaces[3]) && (spaces[3] == spaces[6])){
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    else if((spaces[1] != ' ') &&  (spaces[1] == spaces[4]) && (spaces[4] == spaces[7])){
        spaces[1] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    else if((spaces[2] != ' ') &&  (spaces[2] == spaces[5]) && (spaces[5] == spaces[8])){
        spaces[2] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    //Diagonal
    else if((spaces[0] != ' ') &&  (spaces[0] == spaces[4]) && (spaces[4] == spaces[8])){
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    else if((spaces[2] != ' ') &&  (spaces[2] == spaces[4]) && (spaces[4] == spaces[6])){
        spaces[2] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOSE!" << endl;
    }
    else{
        return false;
    }
    return true;
}

bool checkTie(char *spaces){
    for(int i = 0; i < 9; i++){
        if(spaces[i] == ' '){
            return false;
        }
    }
    cout << "IT'S A TIE!" << endl;
    return true;
}

string getBoardState(char *spaces){
    string state = "";
    for(int i = 0; i < 9; i++){
        state += spaces[i];
    }
    return state;
}