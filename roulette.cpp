// Copyright (c) 2025 Jack Turcotte All rights reserved.
//
// Created by: Jack Turcotte
// Date: May 17, 2025
// Roulette game in C++

#include <algorithm>
#include <cctype>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

const std::string CONTINUE_MSG = "Enter any input to continue:";
const std::string STARTING_MSG = "You've entered a world where chance is king and risk is the price of power.\nStart with a modest sum, claw your way to $1000, and bend fortune to your will...\nIf it doesn't break you first…";

const char* TUTORIAL[] = {
    "You start with a fixed amount of money.",
    "Your goal is to reach $1000.",
    "Each round, place a bet of your choosing.",
    "There's a 1 in 4 chance to lose your bet.",
    "You can buy buffs to reduce your odds of losing or manipulate the outcome.",
    "Winning adds cash. Losing subtracts a lot more.",
    "Spend wisely, bet strategically."
};
const int TUTORIAL_SIZE = sizeof(TUTORIAL) / sizeof(TUTORIAL[0]);

const int DIALOGUE_TIMINGS[] = {
    1, 2, 3, 4, 5
};
const int DIALOGUE_TIMINGS_SIZE = sizeof(DIALOGUE_TIMINGS) / sizeof(DIALOGUE_TIMINGS[0]);
const char* DIALOGUE_LINES[] = {
    "The dealer eyes you up and down, ready to spin the wheel.",
    "A hush falls over the table as you place your bet.",
    "You feel your luck's about to shift. You just don't know which way.",
    "Every click of the wheel hits like a heartbeat in your skull.",
    "You're one bet away from something — you just don't know what."
};
const int DIALOGUE_LINES_SIZE = sizeof(DIALOGUE_LINES) / sizeof(DIALOGUE_LINES[0]);

const char* ITEM_NAMES[] = {
    "Loaded Dice",
    "Fortune's Favor",
    "Echo Bet"};
const char* ITEM_EFFECTS[] = {
    "Avoid a number of your choice.",
    "50% chance to re-spin if you lose.",
    "If you win, win again for free."};
const char* ITEM_DESCRIPTIONS[] = {
    "Tampered and twisted. Luck has a favorite tonight.",
    "She's watching you. Just this once.",
    "A whisper in time. A second chance disguised as déjà vu."};
const float ITEM_PRICE_FRACTIONS[] = {
    0.10f,
    0.15f,
    0.40f
};
const char* ITEM_ACTIVATION_LINES[] = {
    "The dice hum softly. Reality tips in your favor.",
    "A second chance stirs behind the curtain.",
    "The win echoes — once more, just like before."};
const int ITEM_COUNT = sizeof(ITEM_NAMES) / sizeof(ITEM_NAMES[0]);

const int WHEEL_MAX = 4;

// Color print
void c_print(const std::string text, const std::string color) {
    int r = 255, g = 255, b = 255;  // default to white

    if (color == "red") {
        r = 255;
        g = 0;
        b = 0;
    } else if (color == "green") {
        r = 0;
        g = 255;
        b = 0;
    } else if (color == "yellow") {
        r = 255;
        g = 255;
        b = 0;
    } else if (color == "blue") {
        r = 0;
        g = 128;
        b = 255;
    } else if (color == "cyan") {
        r = 0;
        g = 255;
        b = 255;
    } else if (color == "magenta") {
        r = 255;
        g = 0;
        b = 255;
    } else if (color == "white") {
        r = 255;
        g = 255;
        b = 255;
    } else if (color == "gray") {
        r = 128;
        g = 128;
        b = 128;
    } else if (color == "black") {
        r = 0;
        g = 0;
        b = 0;
    } else if (color == "orange") {
        r = 255;
        g = 165;
        b = 0;
    } else if (color == "purple") {
        r = 255;
        g = 10;
        b = 255;
    } else if (color == "pink") {
        r = 255;
        g = 105;
        b = 180;
    }

    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
              << text << "\033[0m"<< std::flush;
}

// === Redraw Terminal ===
void redraw_terminal() {
    system("clear");
    c_print("\n--------JackRoulette--------\n", "white");
}

// === Random int ===
int random_int(int min, int max) {
    static std::mt19937 rng(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// === To lower ===
std::string to_lower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lower;
}

// === Prompt Continue ===
void prompt_continue() {
    for (int counter = 0; counter < CONTINUE_MSG.length();counter++) {
        c_print(std::string(1, CONTINUE_MSG[counter]), "yellow");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::string input;
    std::cin >> input;  // Wait for user input
}
// === Item Activate ===
void item_activate(const std::string& item) {
    for (int item_c; item_c < ITEM_NAMES.length(); item_c++) {
        if (ITEM_NAMES[item_c] == item) {
            c_print("🜲 " + ITEM_ACTIVATION_LINES[item_c], "blue");
            break;
        }
    }
}

std::pair<std::string, int> open_shop(int user_money) {
    std::map<std::string, int> prices;

    std::cout << "\n🛒 Welcome to the Shop! Choose one item to aid your next bet.\n";
    for (int i = 0; i < ITEM_COUNT; ++i) {
        int modifier = random_int(-10, 10);
        int final_price = std::max(1, static_cast<int>(ITEM_PRICE_FRACTIONS[i] * user_money + modifier));
        std::string item_name = ITEM_NAMES[i];
        std::string lower_name = to_lower(item_name);
        prices[lower_name] = final_price;

        std::cout << "\n- " << ITEM_NAMES[i]
                  << "\n  Effect: " << ITEM_EFFECTS[i]
                  << "\n  " << ITEM_DESCRIPTIONS[i]
                  << "\n  💸 Price: $" << final_price << "\n";
    }

    std::cout << "\nEnter the name of the item you want to buy (or press Enter to skip): ";
    std::string choice;
    std::cin.ignore();
    std::getline(std::cin, choice);
    std::string lower_choice = to_lower(choice);

    if (lower_choice.empty()) {
        std::cout << "You walk away empty-handed... for now.\n";
        return {"N/A", user_money};
    }

    if (prices.count(lower_choice)) {
        int price = prices[lower_choice];
        if (user_money >= price) {
            user_money -= price;
            std::cout << "You purchased '" << choice << "' for $" << price << ".\n";
            return {lower_choice, user_money};
        } else {
            std::cout << "You can't afford that. Maybe next round.\n";
        }
    } else {
        std::cout << "That item isn't for sale right now.\n";
    }

    return {"N/A", user_money};
}

int roulette(int bet, const std::string& item) {
    int roll = random_int(1, WHEEL_MAX);
    bool lost = (roll == 1);  // 1 in 4 loss chance
    if (item == "fortune's favor" && lost) {
        if (random_int(1, 2) == 1) {
            lost = false;  // 50% chance to retry
        }
    }

    int earnings = 0;
    if (lost) {
        earnings = -bet * 2;
        c_print("The wheel betrays you. You lose $" + std::to_string(-earnings) + "\n", "red");
    } else {
        earnings = bet;
        c_print("The wheel lands in your favor. You win $" + std::to_string(earnings) + "\n", "green");
    }

    prompt_continue();
    redraw_terminal();
    return earnings;
}

// === Game Loop ===
bool game() {
    redraw_terminal();
    int userMoney = 100;
    bool gameWon = true;

    while (true) {
        if (userMoney >= 1000) {
            gameWon = true;
            break;
        }
        if (userMoney <= 0) {
            gameWon = false;
            break;
        }

        int intensity = 1;
        if (userMoney > 800) {
            intensity = 5;
        } else if (userMoney > 500) {
            intensity = 4;
        } else if (userMoney > 300) {
            intensity = 3;
        } else {
            intensity = 2;
        }
        std::string dialogue = DIALOGUE_LINES[intensity - 1];
        c_print(dialogue, "gray");
        c_print("\nYour current money: "+ std::to_string(userMoney),"cyan");

        std::string visitShop;
        c_print("\nDo you want to visit the shop before placing your bet? (y/n)", "yellow");
        std::cin >> visitShop;

        std::string item = "N/A";

        if (visitShop == "y") {
            auto result = open_shop(userMoney);
            item = result.first;
            userMoney = result.second;
        } else {
            c_print("You ignore the strange merchant lingering in the corner...", "gray");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        try {
            redraw_terminal();
            if (item != "N/A") {
                c_print("You purchased " + item + "\n", "cyan");
            }
            c_print(dialogue, "gray");
            c_print("\nYour current money: " + std::to_string(userMoney), "cyan");

            std::string betString;
            int betInt;

            c_print("\nPlace your bet: ", "yellow");
            std::cin >> betString;

            if (betString == "EzWin") {
                userMoney = 1000;
            } else if (betString == "LoseGame") {
                userMoney = -1;
            } else if (betString == "Boost") {
                userMoney += 300;
            } else {
                betInt = std::stoi(betString);

                if (betInt<0 || betInt>userMoney) {
                    throw std::runtime_error("Bet must be from 0 to your total money.");
                } else {
                    int earnings = roulette(betInt, item);
                    userMoney += earnings;
                }
            }
        } catch (std::invalid_argument) {
            c_print("Warning: Invalid input detected!", "red");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            redraw_terminal();
        }
    }
    std::string retry;
    c_print("Play again? (y/n): ","yellow");
    std::cin >> retry;

    if (retry == "y") {
        return true;
    } else {
        return false;
    }
}

void tutorial() {
    c_print(STARTING_MSG+"\n","cyan");
    std::string doTutorial;

    c_print("Would you like a tutorial? (y/n):", "yellow");
    std::cin >>doTutorial;
    if (doTutorial == "y") {
        for (int msg = 1; msg < TUTORIAL_SIZE; msg++) {
            c_print(std::string(TUTORIAL[msg])+"\n", "white");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } else {
        c_print("Let's get this party started!\n", "green");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    c_print("Traveling to the casino","purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".\n", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// === Main Entry ===
int main() {
    tutorial();
    bool retry = true;
    while (retry == true) {
        retry = game();
    }
    c_print("\nFarewell friend, may the odds be forever in your favour\n", "gray");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    c_print("And remember, 99% of gamblers quit before they win big...", "gray");
    return 0;
}
