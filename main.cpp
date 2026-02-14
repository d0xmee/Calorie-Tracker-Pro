#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <sstream>     
#include <map>      
#include <ctime>
#include "UserProfile.h"
#include "Calculator.h"
#include "FoodDatabase.h"
#include "DataManager.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);  

    stringstream ss;
    ss << setw(2) << setfill('0') << ltm.tm_mday << "-"
        << setw(2) << setfill('0') << 1 + ltm.tm_mon << "-"
        << 1900 + ltm.tm_year;

    return ss.str();
}

void printHeader(const string& title) {
    cout << "\n" << string(50, '=') << endl;
    cout << "     " << title << endl;
    cout << string(50, '=') << endl;
}

int getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max) {
            cout << "Error! Enter a number from " << min << " to " << max << endl;
            clearInput();
        }
        else {
            clearInput();
            return value;
        }
    }
}

double getDoubleInput(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max) {
            cout << "Error! Enter a number from " << min << " to " << max << endl;
            clearInput();
        }
        else {
            clearInput();
            return value;
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

UserProfile createNewUser(DataManager& dataManager) {
    UserProfile user;

    printHeader("CREATE NEW ACCOUNT");

    while (true) {
        user.username = getStringInput("Choose username: ");
        if (dataManager.userExists(user.username)) {
            cout << "Username already exists! Choose another.\n";
        }
        else {
            break;
        }
    }

    user.name = getStringInput("Enter your full name: ");
    user.age = getIntInput("Age (years): ", 1, 120);

    cout << "Gender (1 - Male, 2 - Female): ";
    int gender = getIntInput("", 1, 2);
    user.gender = (gender == 1) ? Gender::MALE : Gender::FEMALE;

    user.weight = getDoubleInput("Weight (kg): ", 20, 300);
    user.height = getDoubleInput("Height (cm): ", 100, 250);

    printHeader("ACTIVITY LEVEL");
    cout << "1 - Sedentary (office job, no exercise)\n";
    cout << "2 - Lightly Active (exercise 1-3 times/week)\n";
    cout << "3 - Moderately Active (exercise 3-5 times/week)\n";
    cout << "4 - Very Active (exercise 6-7 times/week)\n";
    cout << "5 - Extremely Active (athlete, physical labor)\n";

    int activity = getIntInput("Select level (1-5): ", 1, 5);
    user.activity = static_cast<ActivityLevel>(activity - 1);

    printHeader("YOUR GOAL");
    cout << "1 - Weight Loss\n";
    cout << "2 - Maintenance\n";
    cout << "3 - Weight Gain\n";

    int goal = getIntInput("Select goal (1-3): ", 1, 3);
    user.goal = static_cast<Goal>(goal - 1);

    if (dataManager.saveUser(user)) {
        cout << "\n✅ Account created successfully!\n";
    }
    else {
        cout << "\n❌ Error creating account!\n";
    }

    return user;
}

bool loginUser(DataManager& dataManager, UserProfile& user) {
    printHeader("LOGIN");

    vector<string> users = dataManager.getAllUsers();

    if (users.empty()) {
        cout << "No users found. Please create a new account.\n";
        return false;
    }

    cout << "Existing users:\n";
    for (size_t i = 0; i < users.size(); ++i) {
        cout << i + 1 << ". " << users[i] << "\n";
    }
    cout << users.size() + 1 << ". Create new user\n";
    cout << "0. Exit\n";

    int choice = getIntInput("Select option: ", 0, static_cast<int>(users.size() + 1));

    if (choice == 0) return false;

    if (choice == static_cast<int>(users.size() + 1)) {
        user = createNewUser(dataManager);
        dataManager.setCurrentUser(user.username);
        return true;
    }

    string username = users[choice - 1];
    if (dataManager.loadUser(username, user)) {
        dataManager.setCurrentUser(username);
        cout << "\n✅ Welcome back, " << user.name << "!\n";
        return true;
    }

    return false;
}

void displayResults(const UserProfile& user) {
    printHeader("YOUR RESULTS");

    double bmi = Calculator::calculateBMI(user.weight, user.height);
    string bmiCategory = Calculator::getBMICategory(bmi);

    cout << fixed << setprecision(1);
    cout << "Username: " << user.username << endl;
    cout << "Name: " << user.name << endl;
    cout << "Age: " << user.age << " years" << endl;
    cout << "Weight: " << user.weight << " kg" << endl;
    cout << "Height: " << user.height << " cm" << endl;
    cout << "BMI: " << bmi << " (" << bmiCategory << ")" << endl;
    cout << "Activity Level: " << Calculator::getActivityLevelName(user.activity) << endl;
    cout << "Goal: " << Calculator::getGoalName(user.goal) << endl;

    NutritionalNeeds needs = Calculator::calculateNeeds(user);

    cout << "\n" << string(50, '-') << endl;
    cout << "DAILY REQUIREMENTS" << endl;
    cout << string(50, '-') << endl;
    cout << "Calories: " << needs.calories << " kcal" << endl;
    cout << "Protein: " << needs.protein << " g" << endl;
    cout << "Fats: " << needs.fats << " g" << endl;
    cout << "Carbs: " << needs.carbs << " g" << endl;
    cout << "Water: " << needs.water << " L" << endl;
}

void displayDailyLog(DataManager& dataManager, const UserProfile& user) {
    string date = getCurrentDate();
    DailyLog log = dataManager.getDailyLog(date);
    NutritionalNeeds needs = Calculator::calculateNeeds(user);

    printHeader("TODAY'S FOOD LOG (" + date + ")");

    if (log.meals.empty()) {
        cout << "No meals logged today.\n";
    }
    else {
        map<string, vector<FoodLogEntry>> mealsByType;
        for (const auto& meal : log.meals) {
            mealsByType[meal.mealType].push_back(meal);
        }

        for (const auto& [mealType, meals] : mealsByType) {
            cout << "\n--- " << mealType << " ---\n";
            for (const auto& meal : meals) {
                cout << "  • " << meal.foodName << " (" << meal.grams << "g): "
                    << meal.calories << " kcal, "
                    << meal.protein << "g protein, "
                    << meal.fats << "g fats, "
                    << meal.carbs << "g carbs\n";
            }
        }
    }

    cout << "\n" << string(40, '-') << endl;
    cout << "TOTALS FOR TODAY:\n";
    cout << "Calories: " << log.totalCalories << " / " << needs.calories << " kcal ("
        << (log.totalCalories / needs.calories * 100) << "%)\n";
    cout << "Protein: " << log.totalProtein << " / " << needs.protein << " g ("
        << (log.totalProtein / needs.protein * 100) << "%)\n";
    cout << "Fats: " << log.totalFats << " / " << needs.fats << " g ("
        << (log.totalFats / needs.fats * 100) << "%)\n";
    cout << "Carbs: " << log.totalCarbs << " / " << needs.carbs << " g ("
        << (log.totalCarbs / needs.carbs * 100) << "%)\n";
}

void logFoodMenu(DataManager& dataManager, FoodDatabase& db, const UserProfile& user) {
    int choice;
    do {
        printHeader("LOG FOOD");
        cout << "1 - Log breakfast\n";
        cout << "2 - Log lunch\n";
        cout << "3 - Log dinner\n";
        cout << "4 - Log snack\n";
        cout << "5 - View today's log\n";
        cout << "6 - Delete food entry\n";
        cout << "0 - Back\n";

        choice = getIntInput("Select action: ", 0, 6);

        if (choice >= 1 && choice <= 4) {
            string mealType;
            switch (choice) {
            case 1: mealType = "Breakfast"; break;
            case 2: mealType = "Lunch"; break;
            case 3: mealType = "Dinner"; break;
            case 4: mealType = "Snack"; break;
            }

            cout << "Enter food name: ";
            string name;
            cin >> name;

            vector<FoodItem> results = db.searchFoods(name);
            if (results.empty()) {
                cout << "Food not found.\n";
                continue;
            }

            cout << "Found items:\n";
            for (size_t i = 0; i < results.size(); ++i) {
                cout << i + 1 << ". " << results[i].name << " ("
                    << results[i].calories << " kcal/100g)\n";
            }

            int index = getIntInput("Select item number: ", 1, static_cast<int>(results.size())) - 1;
            double grams = getDoubleInput("Enter weight in grams: ", 1, 5000);

            MealEntry meal = db.calculateMeal(results[index], grams);

            FoodLogEntry entry;
            entry.foodName = meal.food.name;
            entry.grams = grams;
            entry.calories = meal.totalCalories;
            entry.protein = meal.totalProtein;
            entry.fats = meal.totalFats;
            entry.carbs = meal.totalCarbs;
            entry.date = getCurrentDate();
            entry.mealType = mealType;

            if (dataManager.saveFoodEntry(entry)) {
                cout << "\n✅ Food logged successfully!\n";
            }
            else {
                cout << "\n❌ Error logging food!\n";
            }
        }

        if (choice == 5) {
            displayDailyLog(dataManager, user);
        }

        if (choice == 6) {
            string date = getCurrentDate();
            auto entries = dataManager.getFoodEntries(date);

            if (entries.empty()) {
                cout << "No entries to delete today.\n";
            }
            else {
                cout << "Today's entries:\n";
                for (size_t i = 0; i < entries.size(); ++i) {
                    cout << i + 1 << ". [" << entries[i].mealType << "] "
                        << entries[i].foodName << " - " << entries[i].grams << "g\n";
                }

                int delChoice = getIntInput("Select entry to delete (0 to cancel): ", 0, static_cast<int>(entries.size()));
                if (delChoice > 0) {
                    auto& entry = entries[delChoice - 1];
                    if (dataManager.deleteFoodEntry(entry.foodName, date, entry.mealType)) {
                        cout << "✅ Entry deleted!\n";
                    }
                }
            }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}

void foodMenu(FoodDatabase& db) {
    int choice;
    do {
        printHeader("FOOD DATABASE");
        cout << "1 - Show all foods\n";
        cout << "2 - Search foods\n";
        cout << "3 - Show categories\n";
        cout << "0 - Back\n";

        choice = getIntInput("Select action: ", 0, 3);

        switch (choice) {
        case 1:
            db.displayFoods();
            break;

        case 2: {
            cout << "Enter search term: ";
            string query;
            cin >> query;
            vector<FoodItem> results = db.searchFoods(query);

            if (results.empty()) {
                cout << "No results found.\n";
            }
            else {
                cout << "\nFound " << results.size() << " items:\n\n";
                for (const auto& food : results) {
                    cout << "- " << food.name << " (" << food.calories
                        << " kcal, " << food.protein << "g protein)\n";
                }
            }
            break;
        }

        case 3: {
            auto categories = db.getCategories();
            cout << "\nFood categories:\n";
            for (const auto& cat : categories) {
                cout << "- " << cat << "\n";
            }
            break;
        }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}

int main() {
    printHeader("WELCOME TO CALORIE TRACKER PRO!");
    cout << "Your personal nutrition assistant\n\n";

    DataManager dataManager;
    FoodDatabase foodDB;
    UserProfile currentUser;

    while (true) {
        printHeader("ACCOUNT MENU");
        cout << "1 - Login\n";
        cout << "2 - Create new account\n";
        cout << "0 - Exit\n";

        int choice = getIntInput("Select option: ", 0, 2);

        if (choice == 0) {
            printHeader("GOODBYE!");
            cout << "Stay healthy!\n\n";
            return 0;
        }

        if (choice == 1) {
            if (loginUser(dataManager, currentUser)) {
                break;
            }
        }
        else if (choice == 2) {
            currentUser = createNewUser(dataManager);
            dataManager.setCurrentUser(currentUser.username);
            break;
        }
    }

    displayResults(currentUser);

    int choice;
    do {
        printHeader("MAIN MENU");
        cout << "1 - Show my results\n";
        cout << "2 - Food database\n";
        cout << "3 - Log food\n";
        cout << "4 - View today's log\n";
        cout << "5 - Switch user / Login\n";
        cout << "6 - Create new user\n";
        cout << "0 - Exit\n";

        choice = getIntInput("Select action: ", 0, 6);

        switch (choice) {
        case 1:
            displayResults(currentUser);
            break;
        case 2:
            foodMenu(foodDB);
            break;
        case 3:
            logFoodMenu(dataManager, foodDB, currentUser);
            break;
        case 4:
            displayDailyLog(dataManager, currentUser);
            break;
        case 5:
            if (loginUser(dataManager, currentUser)) {
                displayResults(currentUser);
            }
            break;
        case 6:
            currentUser = createNewUser(dataManager);
            dataManager.setCurrentUser(currentUser.username);
            displayResults(currentUser);
            break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    printHeader("THANK YOU FOR USING!");
    cout << "Stay healthy, " << currentUser.name << "!\n\n";

    return 0;
}