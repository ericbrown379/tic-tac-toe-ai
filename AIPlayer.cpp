#include "AIPlayer.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

AIPlayer::AIPlayer(char marker, const std::string& key) 
    : Player(marker, "AI"), learningRate(0.1), apiKey(key) {
    // Initialize or load memory
}

int AIPlayer::getMove(const Board& board) {
    // Convert board to string representation
    std::string board_state = board.getBoardState();

    // Make API request
    std::string response = makeOpenAIRequest(board_state);

    // Print the raw response for debugging
    std::cout << "API Response: " << response << std::endl;

    // Parse response
    try {
        json response_json = json::parse(response);
        if (!response_json["choices"].empty() && !response_json["choices"][0]["message"]["content"].is_null()) {
            std::string move_str = response_json["choices"][0]["message"]["content"];
            return std::stoi(move_str) - 1; // Convert to 0-based index
        } else {
            std::cerr << "Invalid response content" << std::endl;
            return 4; // Default move if content is invalid
        }
    } catch (const json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return 4; // Default move if parsing fails
    }
}

std::string AIPlayer::makeOpenAIRequest(const std::string& board_state) {
    CURL* curl = curl_easy_init();
    std::string response;

    if(curl) {
        std::string prompt = "You are playing Tic-Tac-Toe. Here's the current board state:\n" + board_state;
        json request = {
            {"model", "gpt-3.5-turbo"},
            {"messages", {{
                {"role", "user"},
                {"content", prompt}
            }}}
        };

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "{}"; // Return an empty JSON object if the request fails
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return response;
}

size_t AIPlayer::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void AIPlayer::updateMoveValue(const std::string& state, int move, bool won) {
    // Implement logic to update move value
}

void AIPlayer::saveToFile() const {
    // Implement logic to save to file
}

void AIPlayer::loadFromFile() {
    // Implement logic to load from file
} 