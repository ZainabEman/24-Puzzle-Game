#include "header.h"
#include <cctype>

int main() {
    Puzzle game;
    int choice = 0;

    std::cout << "Enter 1 to load puzzle from file (input.txt), or 0 for a random puzzle: ";
    std::cin >> choice;
    if (choice == 1) {
        if (!game.loadInitialFromFile("input.txt")) {
            std::cerr << "Failed to load puzzle from file. Exiting.\n";
            return 1;
        }
    } else {
        game.generateInitialRandom();
    }

    // Game loop
    char moveInput;
    while (true) {
        game.displayBoards();

        if (game.isSolved()) {
            std::cout << "\nCongratulations! You reached the goal state.\n";
            break;
        }

        std::cout << "Enter move (L/R/U/D) or Q to quit: ";
        std::cin >> moveInput;
        if (std::tolower(moveInput) == 'q') {
            std::cout << "Game quit. Better luck next time!\n";
            break;
        }

        if (!game.makeMove(moveInput))
            std::cout << "Please enter a valid move.\n";
    }

    game.printReport("PuzzleReport.txt");
    return 0;
}
