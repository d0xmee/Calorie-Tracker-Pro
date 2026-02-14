#include "Calculator.h"
#include <cmath>

double Calculator::calculateBMR(const UserProfile& user) {
    double bmr;

    if (user.gender == Gender::MALE) {
        bmr = (10 * user.weight) + (6.25 * user.height) - (5 * user.age) + 5;
    }
    else {
        bmr = (10 * user.weight) + (6.25 * user.height) - (5 * user.age) - 161;
    }

    return bmr;
}

double Calculator::calculateTDEE(const UserProfile& user) {
    double bmr = calculateBMR(user);
    double multiplier;

    switch (user.activity) {
    case ActivityLevel::SEDENTARY:
        multiplier = 1.2;
        break;
    case ActivityLevel::LIGHT:
        multiplier = 1.375;
        break;
    case ActivityLevel::MODERATE:
        multiplier = 1.55;
        break;
    case ActivityLevel::ACTIVE:
        multiplier = 1.725;
        break;
    case ActivityLevel::VERY_ACTIVE:
        multiplier = 1.9;
        break;
    default:
        multiplier = 1.2;
    }

    return bmr * multiplier;
}

NutritionalNeeds Calculator::calculateNeeds(const UserProfile& user) {
    double tdee = calculateTDEE(user);
    NutritionalNeeds needs;

    switch (user.goal) {
    case Goal::WEIGHT_LOSS:
        needs.calories = tdee - 500;
        break;
    case Goal::WEIGHT_GAIN:
        needs.calories = tdee + 500;
        break;
    default:
        needs.calories = tdee;
    }

    if (user.goal == Goal::WEIGHT_LOSS) {
        needs.protein = user.weight * 2.2;
        needs.fats = user.weight * 0.8;
    }
    else if (user.goal == Goal::WEIGHT_GAIN) {
        needs.protein = user.weight * 1.8;
        needs.fats = user.weight * 1.0;
    }
    else {
        needs.protein = user.weight * 1.6;
        needs.fats = user.weight * 0.9;
    }

    double caloriesFromProtein = needs.protein * 4;
    double caloriesFromFats = needs.fats * 9;
    needs.carbs = (needs.calories - caloriesFromProtein - caloriesFromFats) / 4;
    needs.water = user.weight * 0.035;

    return needs;
}

double Calculator::calculateBMI(double weight, double height) {
    double heightInMeters = height / 100.0;
    return weight / (heightInMeters * heightInMeters);
}

std::string Calculator::getBMICategory(double bmi) {
    if (bmi < 16.0) return "Severe underweight";
    if (bmi < 18.5) return "Underweight";
    if (bmi < 25.0) return "Normal weight";
    if (bmi < 30.0) return "Overweight";
    if (bmi < 35.0) return "Obese Class I";
    if (bmi < 40.0) return "Obese Class II";
    return "Obese Class III";
}

std::string Calculator::getActivityLevelName(ActivityLevel level) {
    switch (level) {
    case ActivityLevel::SEDENTARY: return "Sedentary";
    case ActivityLevel::LIGHT: return "Lightly Active";
    case ActivityLevel::MODERATE: return "Moderately Active";
    case ActivityLevel::ACTIVE: return "Very Active";
    case ActivityLevel::VERY_ACTIVE: return "Extremely Active";
    default: return "Unknown";
    }
}

std::string Calculator::getGoalName(Goal goal) {
    switch (goal) {
    case Goal::WEIGHT_LOSS: return "Weight Loss";
    case Goal::MAINTENANCE: return "Maintenance";
    case Goal::WEIGHT_GAIN: return "Weight Gain";
    default: return "Unknown";
    }
}