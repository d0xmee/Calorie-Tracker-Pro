#pragma once
#include <string>
#include <vector>

enum class Gender { MALE, FEMALE };
enum class ActivityLevel {
    SEDENTARY,
    LIGHT,
    MODERATE,
    ACTIVE,
    VERY_ACTIVE
};

enum class Goal {
    WEIGHT_LOSS,
    MAINTENANCE,
    WEIGHT_GAIN
};

struct UserProfile {
    std::string username;
    std::string name;
    int age;
    Gender gender;
    double weight;
    double height;
    ActivityLevel activity;
    Goal goal;

    std::string toString() const;
    static UserProfile fromString(const std::string& data);
};

struct FoodLogEntry {
    std::string foodName;
    double grams;
    double calories;
    double protein;
    double fats;
    double carbs;
    std::string date;
    std::string mealType;
};

struct DailyLog {
    std::string date;
    std::vector<FoodLogEntry> meals;
    double totalCalories;
    double totalProtein;
    double totalFats;
    double totalCarbs;
};