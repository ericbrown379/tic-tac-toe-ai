#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

class Config {
public:
    static void init();
    static std::string getApiKey();

private:
    static std::string api_key;
    
    static void loadEnvFile() {
        std::ifstream envFile(".env");
        if (!envFile.is_open()) {
            throw std::runtime_error("Could not open .env file");
        }

        std::string line;
        while (std::getline(envFile, line)) {
            if (line.find("OPENAI_API_KEY=") == 0) {
                api_key = line.substr(14); // Length of "OPENAI_API_KEY="
                break;
            }
        }
    }
};