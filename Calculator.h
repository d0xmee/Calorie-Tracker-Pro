#pragma once
#include "UserProfile.h"
#include <string>

struct NutritionalNeeds {
    double calories;
    double protein;
    double fats;
    double carbs;
    double water;
};

class Calculator {
public:
    static double calculateBMR(const UserProfile& user);
    static double calculateTDEE(const UserProfile& user);
    static NutritionalNeeds calculateNeeds(const UserProfile& user);
    static double calculateBMI(double weight, double height);
    static std::string getBMICategory(double bmi);
    static std::string getActivityLevelName(ActivityLevel level);
    static std::string getGoalName(Goal goal);
};