# Calorie Tracker Pro 🥗

![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Build](https://img.shields.io/badge/build-Visual%20Studio%202022-purple.svg)

<div align="center">
  <img src="https://img.icons8.com/color/96/000000/calories--v1.png"/>
  <h3>Your Personal Nutrition Assistant</h3>
  <p><i>Calculate, Track, and Achieve Your Health Goals</i></p>
</div>

---

## 📑 Table of Contents
- [About The Project](#-about-the-project)
- [Features](#-features)
- [Getting Started](#-getting-started)
- [Installation](#-installation)
- [Usage Guide](#-usage-guide)
- [Calculation Methods](#-calculation-methods)
- [Food Database](#-food-database)
- [Project Structure](#-project-structure)
- [Technical Details](#-technical-details)
- [Contributing](#-contributing)
- [License](#-license)
- [Contact](#-contact)

---

## 🎯 About The Project

**Calorie Tracker Pro** is a comprehensive console-based nutrition tracking application built with C++. It helps users calculate their daily caloric needs, track food intake, and maintain a healthy lifestyle through personalized nutrition recommendations with full data persistence.

---

## ✨ Features

### 📊 Personal Calculations
- **BMR** - Basal Metabolic Rate using Mifflin-St Jeor Equation
- **TDEE** - Total Daily Energy Expenditure with activity multipliers
- **BMI** - Body Mass Index with health category interpretation
- **Macronutrients** - Custom protein, fat, and carbohydrate recommendations
- **Hydration** - Daily water intake recommendations

### 👥 User Management
- Multiple user profiles
- Unique username login
- Individual settings and history
- Automatic data persistence

### 📝 Food Diary
- Log meals (Breakfast, Lunch, Dinner, Snack)
- Automatic calorie and macro calculation
- Daily statistics and progress tracking
- Delete and edit entries

### 🍎 Food Database
- 25+ common foods
- 8 categories
- Search by name
- Portion calculator

---

## 🚀 Getting Started

### Prerequisites
- Windows 10/11
- Visual Studio 2022 with Desktop Development for C++

---

## 📥 Installation

### Quick Start
```bash
git clone https://github.com/yourusername/calorie-tracker-pro.git
cd calorie-tracker-pro
Then open CalorieTracker.sln in Visual Studio 2022 and press Ctrl+F5 to run.

📖 Usage Guide
Account Menu
text
══════════════════════════════════════════════
              ACCOUNT MENU
══════════════════════════════════════════════
1 - Login
2 - Create new account
0 - Exit
Main Menu
text
══════════════════════════════════════════════
              MAIN MENU
══════════════════════════════════════════════
1 - Show my results
2 - Food database
3 - Log food
4 - View today's log
5 - Switch user
6 - Create new user
0 - Exit
📊 Calculation Methods
Formulas
text
BMR (Male)   = (10 × weight) + (6.25 × height) - (5 × age) + 5
BMR (Female) = (10 × weight) + (6.25 × height) - (5 × age) - 161
TDEE         = BMR × Activity Multiplier
BMI          = weight(kg) / (height(m))²
Water        = weight × 0.035 L
Activity Multipliers
Level	Multiplier
Sedentary	1.2
Light	1.375
Moderate	1.55
Active	1.725
Very Active	1.9
BMI Categories
Range	Category
< 16.0	Severe underweight
16.0 - 18.4	Underweight
18.5 - 24.9	Normal weight
25.0 - 29.9	Overweight
30.0 - 34.9	Obese Class I
35.0 - 39.9	Obese Class II
≥ 40.0	Obese Class III
🥗 Food Database
Food	kcal	Protein	Fats	Carbs
Chicken Breast	165	31.0g	3.6g	0.0g
Salmon	208	20.0g	13.0g	0.0g
Egg	157	12.7g	11.5g	0.7g
Oatmeal	88	3.2g	1.8g	15.0g
Banana	96	1.5g	0.2g	22.0g
Apple	52	0.3g	0.2g	14.0g
Rice	130	2.7g	0.3g	28.0g
Broccoli	34	2.8g	0.4g	6.6g
*All values per 100g. Full database includes 25+ items.*

🗂️ Project Structure
text
CalorieTracker/
├── 📁 CalorieTracker/
│   ├── 📄 main.cpp
│   ├── 📄 UserProfile.h/cpp
│   ├── 📄 Calculator.h/cpp
│   ├── 📄 FoodDatabase.h/cpp
│   └── 📄 DataManager.h/cpp
├── 📁 CalorieTrackerData/
│   ├── 📁 users/
│   └── 📁 logs/
├── 📄 CalorieTracker.sln
└── 📄 README.md
🔧 Technical Details
Language: C++17

Compiler: MSVC (Visual Studio 2022)

Dependencies: Standard Library only

Data Storage: Text files in local directory

🤝 Contributing
Fork the Project

Create your Feature Branch (git checkout -b feature/AmazingFeature)

Commit your Changes (git commit -m 'Add AmazingFeature')

Push to the Branch (git push origin feature/AmazingFeature)

Open a Pull Request

📄 License
MIT License © 2024 Calorie Tracker Pro

📬 Contact
Project Link: https://github.com/d0xmee/calorie-tracker-pro

<div align="center"> <p>⭐ Star this project if you find it useful! ⭐</p> <p>Made with ❤️ for a healthier world</p> </div> ```
