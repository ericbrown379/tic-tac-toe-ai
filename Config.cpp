#include "Config.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib> // For std::getenv

std::string Config::api_key = ""; // Define the static variable

void Config::init() {
    // Load API key from environment variable
    const char* env_api_key = std::getenv("OPENAI_API_KEY");
    if (env_api_key) {
        api_key = env_api_key;
    } else {
        throw std::runtime_error("API key not found in environment variables");
    }
}

std::string Config::getApiKey() {
    return api_key;
} 