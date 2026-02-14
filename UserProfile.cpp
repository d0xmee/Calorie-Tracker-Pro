#include "UserProfile.h"
#include <sstream>
#include <iomanip>
#include <string>

std::string UserProfile::toString() const {
    std::stringstream ss;
    ss << username << "|"
        << name << "|"
        << age << "|"
        << static_cast<int>(gender) << "|"
        << weight << "|"
        << height << "|"
        << static_cast<int>(activity) << "|"
        << static_cast<int>(goal);
    return ss.str();
}

UserProfile UserProfile::fromString(const std::string& data) {
    UserProfile user;
    std::stringstream ss(data);
    std::string token;

    std::getline(ss, token, '|'); user.username = token;
    std::getline(ss, token, '|'); user.name = token;
    std::getline(ss, token, '|'); user.age = std::stoi(token);
    std::getline(ss, token, '|'); user.gender = static_cast<Gender>(std::stoi(token));
    std::getline(ss, token, '|'); user.weight = std::stod(token);
    std::getline(ss, token, '|'); user.height = std::stod(token);
    std::getline(ss, token, '|'); user.activity = static_cast<ActivityLevel>(std::stoi(token));
    std::getline(ss, token, '|'); user.goal = static_cast<Goal>(std::stoi(token));

    return user;
}