#ifndef PUZZLE_H
#define PUZZLE_H

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <cctype>

// The Puzzle class encapsulates a 5x5 sliding puzzle game.
// The blank tile is represented by the number (size*size) i.e. 25.
class Puzzle {
public:
    static const int size = 5;

    // Constructor: seeds the random generator and generates a random goal board.
    Puzzle() : moveCount(0) {
        std::random_device rd;
        rng.seed(rd());
        generateGoal();
    }

    // Generates a random goal board.
    void generateGoal() {
        goalBoard = generateRandomBoard();
    }

    // Generates a random initial board that is solvable.
    void generateInitialRandom() {
        do {
            currentBoard = generateRandomBoard();
        } while (!isSolvable());
        movePath.clear();
        moveCount = 0;
    }

    // Loads the initial board from a text file.
    // The file should contain exactly 25 numbers.
    bool loadInitialFromFile(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error opening file: " << filename << "\n";
            return false;
        }
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (!(infile >> currentBoard[i][j])) {
                    std::cerr << "Error reading board data from file.\n";
                    return false;
                }
        infile.close();
        if (!isSolvable()) {
            std::cerr << "The loaded puzzle is not solvable.\n";
            return false;
        }
        movePath.clear();
        moveCount = 0;
        return true;
    }

    // Displays a given board.
    void displayBoard(const std::array<std::array<int, size>, size>& board) const {
        for (const auto& row : board) {
            std::cout << "\t";
            for (const auto& tile : row) {
                if (tile == size * size)
                    std::cout << "   \t";  // blank tile
                else
                    std::cout << tile << "\t";
            }
            std::cout << "\n\n";
        }
    }

    // Displays both the goal board and the current board.
    // Uses ANSI escape codes to clear the screen and reposition the cursor.
    void displayBoards() const {
        std::cout << "\033[2J\033[H";  // Clear screen and move cursor to home position
        std::cout << "\nGoal State:\n";
        displayBoard(goalBoard);
        std::cout << "\nCurrent State:\n";
        displayBoard(currentBoard);
        std::cout << "\nLegal Moves: ";
        for (const auto& move : getLegalMoves())
            std::cout << move << " ";
        std::cout << "\n";
    }

    // Returns the legal moves for the blank tile as a vector of strings.
    std::vector<std::string> getLegalMoves() const {
        std::vector<std::string> moves;
        auto [row, col] = findBlank(currentBoard);
        if (col > 0)             moves.push_back("Left");
        if (col < size - 1)        moves.push_back("Right");
        if (row > 0)             moves.push_back("Up");
        if (row < size - 1)        moves.push_back("Down");
        return moves;
    }

    // Attempts to perform a move given a direction character ('L', 'R', 'U', 'D'; case-insensitive).
    // Returns true if the move is successful.
    bool makeMove(char direction) {
        direction = std::tolower(direction);
        auto [row, col] = findBlank(currentBoard);
        int newRow = row, newCol = col;
        switch (direction) {
            case 'l': newCol = col - 1; break;
            case 'r': newCol = col + 1; break;
            case 'u': newRow = row - 1; break;
            case 'd': newRow = row + 1; break;
            default:
                std::cout << "Invalid input. Use L, R, U, or D.\n";
                return false;
        }
        if (newRow < 0 || newRow >= size || newCol < 0 || newCol >= size) {
            std::cout << "Move not allowed from current position.\n";
            return false;
        }
        std::swap(currentBoard[row][col], currentBoard[newRow][newCol]);
        movePath.push_back(direction);
        ++moveCount;
        return true;
    }

    // Checks whether the current board matches the goal board.
    bool isSolved() const {
        return currentBoard == goalBoard;
    }

    // Prints a report of the moves made to both the console and a text file.
    void printReport(const std::string& reportFilename) const {
        std::ofstream outFile(reportFilename);
        if (!outFile) {
            std::cerr << "Error creating report file.\n";
            return;
        }
        std::ostringstream report;
        report << "Puzzle Report:\n"
               << "Total moves: " << moveCount << "\n"
               << "Move sequence: ";
        for (const auto& move : movePath) {
            switch (move) {
                case 'u': report << "UP "; break;
                case 'd': report << "DOWN "; break;
                case 'l': report << "LEFT "; break;
                case 'r': report << "RIGHT "; break;
                default:  report << move << " "; break;
            }
        }
        const std::string reportStr = report.str();
        outFile << reportStr;
        outFile.close();
        std::cout << "\n" << reportStr << "\n";
        std::cout << "Detailed report available in: " << reportFilename << "\n";
    }

private:
    std::array<std::array<int, size>, size> currentBoard;
    std::array<std::array<int, size>, size> goalBoard;
    std::vector<char> movePath;
    int moveCount;

    // Generates a random board (a random permutation of numbers 1 to size*size).
    std::array<std::array<int, size>, size> generateRandomBoard() {
        std::array<int, size * size> numbers;
        for (int i = 0; i < size * size; ++i)
            numbers[i] = i + 1;
        std::shuffle(numbers.begin(), numbers.end(), rng);
        std::array<std::array<int, size>, size> board{};
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                board[i][j] = numbers[i * size + j];
        return board;
    }

    // Finds and returns the (row, column) position of the blank tile (represented by size*size).
    std::pair<int, int> findBlank(const std::array<std::array<int, size>, size>& board) const {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == size * size)
                    return { i, j };
        return { -1, -1 }; // Should not occur.
    }

    // Counts inversions in a board (ignoring the blank tile).
    int countInversions(const std::array<std::array<int, size>, size>& board) const {
        std::vector<int> flat;
        for (const auto& row : board)
            for (const auto& tile : row)
                flat.push_back(tile);
        int invCount = 0;
        for (size_t i = 0; i < flat.size(); ++i)
            for (size_t j = i + 1; j < flat.size(); ++j)
                if (flat[i] != size * size && flat[j] != size * size && flat[i] > flat[j])
                    ++invCount;
        return invCount;
    }

    // Determines if the current puzzle is solvable by comparing inversion parity with the goal board.
    bool isSolvable() const {
        int invCurrent = countInversions(currentBoard);
        int invGoal = countInversions(goalBoard);
        return (invCurrent % 2) == (invGoal % 2);
    }

    std::mt19937 rng{ std::chrono::steady_clock::now().time_since_epoch().count() };
};

#endif // PUZZLE_H
