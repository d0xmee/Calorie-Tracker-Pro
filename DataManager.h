#pragma once
#include "UserProfile.h"
#include <string>
#include <vector>
#include <map>

class DataManager {
private:
    std::string dataDirectory;
    std::string currentUser;
    UserProfile currentProfile;
    std::map<std::string, std::vector<FoodLogEntry>> foodLogs;

    bool createDataDirectory();
    std::string getUserFilePath(const std::string& username);
    std::string getLogFilePath(const std::string& username, const std::string& date);

public:
    DataManager();

    bool userExists(const std::string& username);
    bool saveUser(const UserProfile& user);
    bool loadUser(const std::string& username, UserProfile& user);
    std::vector<std::string> getAllUsers();
    bool setCurrentUser(const std::string& username);
    UserProfile getCurrentUser() const { return currentProfile; }

    bool saveFoodEntry(const FoodLogEntry& entry);
    std::vector<FoodLogEntry> getFoodEntries(const std::string& date);
    DailyLog getDailyLog(const std::string& date);
    bool deleteFoodEntry(const std::string& foodName, const std::string& date, const std::string& mealType);
};