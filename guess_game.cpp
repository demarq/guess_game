#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <variant>
#include <type_traits>
#include <random>

using int_str_bool = std::variant<std::string, bool, int>;

// Configuration map with initial game settings
std::unordered_map<std::string, std::string> config = {
    {"min_value", "1"},
    {"max_value", "100"},
    {"game_name", "Guess"}
};

// Function to pick a random number in the range [min_value, max_value]
int pick_random_int() {
    std::random_device rd;
    std::mt19937_64 gen(rd());

    int from = std::stoi(config["min_value"]);
    int to = std::stoi(config["max_value"]);

    std::uniform_int_distribution<> distrib(from, to);
    return distrib(gen);
}

// Main game loop
void play_game() {
    std::stringstream greetings_line;

    std::string user_name;
    std::cout << "Hello! Please insert your name: ";
    std::cin >> user_name;

    greetings_line << "Thank you " << user_name << "!\nLet's play '" \
        << config["game_name"] << "'! By the game rules, you need to guess a number from " \
        << config["min_value"] << " to " << config["max_value"];

    std::cout << greetings_line.str() << std::endl;

    std::string user_input;
    int number_to_guess = pick_random_int();
    int number;

    // Main guessing loop
    while (true) {
        std::cout << "Please insert your guess: ";
        std::cin >> user_input;

        try {
            number = std::stoi(user_input);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Please insert only numbers.\n";
            continue;
        }

        if (number < number_to_guess) {
            std::cout << "Greater!\n";
        }
        else if (number > number_to_guess) {
            std::cout << "Lower!\n";
        }
        else {
            std::cout << "Finally! You guessed correctly!\n";
            break;
        }
    }
}

int main() {
    std::string user_restart_input;

    // Loop to allow restarting the game
    do {
        play_game();  // Start the game

        // Ask if the player wants to restart
        std::cout << "Do you wish to play again? (y/N)\n";
        std::cin >> user_restart_input;

    } while (user_restart_input == "y");

    std::cout << "Thanks for playing!\n";
    return 0;
}