#pragma once
#include <string>
#include <vector>
#include <map>

struct FoodItem {
    std::string name;
    double calories;
    double protein;
    double fats;
    double carbs;
    std::string category;
};

struct MealEntry {
    FoodItem food;
    double grams;
    double totalCalories;
    double totalProtein;
    double totalFats;
    double totalCarbs;
};

class FoodDatabase {
private:
    std::vector<FoodItem> foods;
    std::map<std::string, std::vector<FoodItem>> foodsByCategory;

public:
    FoodDatabase();
    void loadDefaultFoods();
    void addFood(const FoodItem& food);
    std::vector<FoodItem> searchFoods(const std::string& query);
    std::vector<FoodItem> getFoodsByCategory(const std::string& category);
    void displayFoods();
    MealEntry calculateMeal(const FoodItem& food, double grams);
    std::vector<std::string> getCategories();
};