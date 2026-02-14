#include "DataManager.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <map>     

namespace fs = std::filesystem;

DataManager::DataManager() {
    dataDirectory = "CalorieTrackerData";
    createDataDirectory();
}

bool DataManager::createDataDirectory() {
    try {
        if (!fs::exists(dataDirectory)) {
            fs::create_directory(dataDirectory);
        }

        std::string usersDir = dataDirectory + "/users";
        if (!fs::exists(usersDir)) {
            fs::create_directory(usersDir);
        }

        std::string logsDir = dataDirectory + "/logs";
        if (!fs::exists(logsDir)) {
            fs::create_directory(logsDir);
        }

        return true;
    }
    catch (...) {
        return false;
    }
}

std::string DataManager::getUserFilePath(const std::string& username) {
    return dataDirectory + "/users/" + username + ".txt";
}

std::string DataManager::getLogFilePath(const std::string& username, const std::string& date) {
    return dataDirectory + "/logs/" + username + "_" + date + ".txt";
}

bool DataManager::userExists(const std::string& username) {
    return fs::exists(getUserFilePath(username));
}

bool DataManager::saveUser(const UserProfile& user) {
    std::string filepath = getUserFilePath(user.username);
    std::ofstream file(filepath);

    if (file.is_open()) {
        file << user.toString();
        file.close();
        return true;
    }
    return false;
}

bool DataManager::loadUser(const std::string& username, UserProfile& user) {
    std::string filepath = getUserFilePath(username);
    std::ifstream file(filepath);

    if (file.is_open()) {
        std::string data;
        std::getline(file, data);
        user = UserProfile::fromString(data);
        file.close();
        return true;
    }
    return false;
}

std::vector<std::string> DataManager::getAllUsers() {
    std::vector<std::string> users;
    std::string usersPath = dataDirectory + "/users";

    try {
        for (const auto& entry : fs::directory_iterator(usersPath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                size_t pos = filename.find_last_of(".");
                if (pos != std::string::npos) {
                    users.push_back(filename.substr(0, pos));
                }
            }
        }
    }
    catch (...) {}

    return users;
}

bool DataManager::setCurrentUser(const std::string& username) {
    if (loadUser(username, currentProfile)) {
        currentUser = username;
        return true;
    }
    return false;
}

bool DataManager::saveFoodEntry(const FoodLogEntry& entry) {
    if (currentUser.empty()) return false;

    std::string filepath = getLogFilePath(currentUser, entry.date);
    std::ofstream file(filepath, std::ios::app);

    if (file.is_open()) {
        file << entry.foodName << "|"
            << entry.grams << "|"
            << entry.calories << "|"
            << entry.protein << "|"
            << entry.fats << "|"
            << entry.carbs << "|"
            << entry.mealType << "\n";
        file.close();
        return true;
    }
    return false;
}

std::vector<FoodLogEntry> DataManager::getFoodEntries(const std::string& date) {
    std::vector<FoodLogEntry> entries;
    if (currentUser.empty()) return entries;

    std::string filepath = getLogFilePath(currentUser, date);
    std::ifstream file(filepath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            FoodLogEntry entry;
            std::string token;

            std::getline(ss, token, '|'); entry.foodName = token;
            std::getline(ss, token, '|'); entry.grams = std::stod(token);
            std::getline(ss, token, '|'); entry.calories = std::stod(token);
            std::getline(ss, token, '|'); entry.protein = std::stod(token);
            std::getline(ss, token, '|'); entry.fats = std::stod(token);
            std::getline(ss, token, '|'); entry.carbs = std::stod(token);
            std::getline(ss, token, '|'); entry.mealType = token;
            entry.date = date;

            entries.push_back(entry);
        }
        file.close();
    }

    return entries;
}

DailyLog DataManager::getDailyLog(const std::string& date) {
    DailyLog log;
    log.date = date;
    log.totalCalories = 0;
    log.totalProtein = 0;
    log.totalFats = 0;
    log.totalCarbs = 0;

    log.meals = getFoodEntries(date);

    for (const auto& meal : log.meals) {
        log.totalCalories += meal.calories;
        log.totalProtein += meal.protein;
        log.totalFats += meal.fats;
        log.totalCarbs += meal.carbs;
    }

    return log;
}

bool DataManager::deleteFoodEntry(const std::string& foodName, const std::string& date, const std::string& mealType) {
    if (currentUser.empty()) return false;

    std::string filepath = getLogFilePath(currentUser, date);
    std::ifstream file(filepath);
    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, type;
            std::getline(ss, name, '|');

            for (int i = 0; i < 6; i++) {
                std::getline(ss, type, '|');
            }

            if (name != foodName || type != mealType) {
                lines.push_back(line);
            }
        }
        file.close();
    }

    std::ofstream outFile(filepath);
    if (outFile.is_open()) {
        for (const auto& line : lines) {
            outFile << line << "\n";
        }
        outFile.close();
        return true;
    }

    return false;
}