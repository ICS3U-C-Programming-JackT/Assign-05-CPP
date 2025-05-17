// Copyright (c) 2025 Jack Turcotte All rights reserved.
//
// Created by: Jack Turcotte
// Date: May 17, 2025
// Roulette game in C++

#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

const std::string CONTINUE_MSG = "Press enter to continue:";

const std::string STARTING_MSG = "You've entered a world where chance is king and risk is the price of power. Start with a modest sum and claw your way to $1000, and bend fortune to your will... If it doesn't break you first…";

const char* TUTORIAL[] = {
    "You start with a fixed amount of money.",
    "Your goal is to reach $1000.",
    "Each round, place a bet of your choosing.",
    "There's a 1 in 4 chance to lose your bet.",
    "You can buy buffs to reduce your odds of losing or manipulate the outcome.",
    "Winning adds cash. Losing subtracts a lot more.",
    "Spend wisely, bet strategically."};
const int TUTORIAL_SIZE = sizeof(TUTORIAL) / sizeof(TUTORIAL[0]);

const int DIALOGUE_TIMINGS[] = {
    1, 1, 3, 4, 3, 5, 4, 3, 2, 5};
const int DIALOGUE_TIMINGS_SIZE = sizeof(DIALOGUE_TIMINGS) / sizeof(DIALOGUE_TIMINGS[0]);

const char* DIALOGUE_LINES[] = {
    "The dealer eyes you up and down, ready to spin the wheel.",
    "A hush falls over the table as you place your bet.",
    "You feel a twinge in your gut. Something's off this round.",
    "The wheel groans louder than before — like it knows your odds.",
    "Your hands shake as the stack of cash gets smaller.",
    "Every click of the wheel hits like a heartbeat in your skull.",
    "A cold breeze drifts in. You swear you see the dealer grin.",
    "You feel your luck's about to shift. You just don't know which way.",
    "It's too quiet. Like the room's holding its breath.",
    "You're one bet away from something — you just don't know what."};
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
    0.40f};

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
        r = 128;
        g = 0;
        b = 128;
    } else if (color == "pink") {
        r = 255;
        g = 105;
        b = 180;
    }

    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
              << text << "\033[0m" << std::endl;
}

// === Redraw Terminal ===
void redraw_terminal() {
    system("clear");
    c_print("--------JackRoulette--------", "white");
}

// === Prompt Continue ===
void prompt_continue() {
    // Empty for now
}

// === Item Activate ===
void item_activate(const std::string& item) {
    // Empty for now
}

// === Shop ===
std::string open_shop(int user_money) {
    //Empty
}

// === Roulette Spin ===
int roulette(int bet, const std::string& item) {
    if (item != "N/A") {
        // Do something with item
    }

    int losing_number = 0;

    for (int spin = 0; spin < 50; ++spin) {
        // Spinning effect
    }

    bool lost = false;

    if (item == "paranoia charm" && lost) {
        return 0;
    }

    int earnings = 0;

    if (lost) {

    } else{

    }

    prompt_continue();
    return earnings;
}

// === Game Loop ===
void game() {
    redraw_terminal();
    int user_money = 100;
    bool game_won = true;

    while (true) {
        int intensity = 1;
        if (user_money > 800) {
            intensity = 5;
        } else if (user_money > 500) {
            intensity = 4;
        } else if (user_money > 300) {
            intensity = 3;
        } else {
            intensity = 2;
        }
    }
}

void tutorial() {
    c_print(STARTING_MSG,"cyan");
    std::string doTutorial;

    c_print("Would you like a tutorial? (y/n):", "yellow");
    std::cin >>doTutorial;

    if (doTutorial == "y") {
        for (int msg = 1; msg < TUTORIAL_SIZE; msg++) {
            c_print(TUTORIAL[msg], "white");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } else {
        c_print("Let's get this party started!", "green");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    c_print("Traveling to the casino","purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    c_print(".", "purple");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// === Main Entry ===
int main() {
    tutorial();
    game();
    return 0;
}
