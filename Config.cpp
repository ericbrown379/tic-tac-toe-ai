#include "Config.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::string Config::api_key = ""; // Define the static variable

void Config::init() {
    // Load configuration, e.g., API keys
    api_key = "your_api_key_here"; // Replace with actual logic
}

std::string Config::getApiKey() {
    return api_key;
} 