#include "FoodDatabase.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

FoodDatabase::FoodDatabase() {
    loadDefaultFoods();
}

void FoodDatabase::loadDefaultFoods() {
    foods.push_back({ "Cucumber", 15, 0.8, 0.1, 3.0, "Vegetables" });
    foods.push_back({ "Tomato", 18, 0.9, 0.2, 3.9, "Vegetables" });
    foods.push_back({ "Cabbage", 25, 1.8, 0.1, 4.7, "Vegetables" });
    foods.push_back({ "Broccoli", 34, 2.8, 0.4, 6.6, "Vegetables" });
    foods.push_back({ "Carrot", 41, 1.3, 0.1, 9.3, "Vegetables" });

    foods.push_back({ "Apple", 52, 0.3, 0.2, 14.0, "Fruits" });
    foods.push_back({ "Banana", 96, 1.5, 0.2, 22.0, "Fruits" });
    foods.push_back({ "Orange", 43, 0.9, 0.1, 11.0, "Fruits" });
    foods.push_back({ "Strawberry", 32, 0.7, 0.3, 7.7, "Fruits" });

    foods.push_back({ "Chicken Breast", 165, 31.0, 3.6, 0.0, "Meat" });
    foods.push_back({ "Beef", 250, 26.0, 15.0, 0.0, "Meat" });
    foods.push_back({ "Salmon", 208, 20.0, 13.0, 0.0, "Fish" });
    foods.push_back({ "Tuna", 184, 29.0, 6.0, 0.0, "Fish" });

    foods.push_back({ "Cottage Cheese", 145, 21.0, 5.0, 3.0, "Dairy" });
    foods.push_back({ "Yogurt", 60, 5.0, 3.0, 4.0, "Dairy" });
    foods.push_back({ "Milk", 52, 3.0, 2.5, 4.7, "Dairy" });
    foods.push_back({ "Cheese", 350, 25.0, 28.0, 0.0, "Dairy" });

    foods.push_back({ "White Rice", 130, 2.7, 0.3, 28.0, "Grains" });
    foods.push_back({ "Buckwheat", 110, 4.2, 1.1, 21.3, "Grains" });
    foods.push_back({ "Oatmeal", 88, 3.2, 1.8, 15.0, "Grains" });
    foods.push_back({ "Pasta", 131, 5.0, 0.5, 27.0, "Grains" });

    foods.push_back({ "Egg", 157, 12.7, 11.5, 0.7, "Eggs" });

    foods.push_back({ "Walnut", 654, 15.2, 65.2, 13.7, "Nuts" });
    foods.push_back({ "Almond", 609, 18.6, 53.7, 13.0, "Nuts" });

    for (const auto& food : foods) {
        foodsByCategory[food.category].push_back(food);
    }
}

void FoodDatabase::addFood(const FoodItem& food) {
    foods.push_back(food);
    foodsByCategory[food.category].push_back(food);
}

std::vector<FoodItem> FoodDatabase::searchFoods(const std::string& query) {
    std::vector<FoodItem> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& food : foods) {
        std::string lowerName = food.name;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerQuery) != std::string::npos) {
            results.push_back(food);
        }
    }

    return results;
}

std::vector<FoodItem> FoodDatabase::getFoodsByCategory(const std::string& category) {
    return foodsByCategory[category];
}

void FoodDatabase::displayFoods() {
    std::cout << "\n=== FOOD DATABASE ===\n";
    std::cout << std::left << std::setw(20) << "Name"
        << std::setw(10) << "Calories"
        << std::setw(10) << "Protein"
        << std::setw(10) << "Fats"
        << std::setw(10) << "Carbs"
        << std::setw(15) << "Category" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& food : foods) {
        std::cout << std::left << std::setw(20) << food.name.substr(0, 19)
            << std::setw(10) << food.calories
            << std::setw(10) << food.protein
            << std::setw(10) << food.fats
            << std::setw(10) << food.carbs
            << std::setw(15) << food.category << std::endl;
    }
}

MealEntry FoodDatabase::calculateMeal(const FoodItem& food, double grams) {
    MealEntry entry;
    entry.food = food;
    entry.grams = grams;
    entry.totalCalories = (food.calories * grams) / 100.0;
    entry.totalProtein = (food.protein * grams) / 100.0;
    entry.totalFats = (food.fats * grams) / 100.0;
    entry.totalCarbs = (food.carbs * grams) / 100.0;

    return entry;
}

std::vector<std::string> FoodDatabase::getCategories() {
    std::vector<std::string> categories;
    for (const auto& pair : foodsByCategory) {
        categories.push_back(pair.first);
    }
    return categories;
}