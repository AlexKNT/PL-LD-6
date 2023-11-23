#include <iostream>
#include <fstream>
#include <cstring>


bool readField(const char* fileName, char field[10][10]) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (!(file >> field[i][j])) {
                std::cerr << "Error: Invalid format in file " << fileName << std::endl;
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

bool saveResult(const char* fileName, int x, int y) {
    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return false;
    }

    char column = 'A' + x;
    int row = y;

    file << column << row << std::endl;

    file.close();
    return true;
}

char getCell(const char field[10][10], int x, int y, char fig) {
    // Define directions
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

    // Check if coordinates are out of bounds
    if (x < 0 || x >= 10 || y < 0 || y >= 10) {
        return 'E'; // Out of bounds
    }

    // Check the specified direction
    int newX = x + dx[dir];
    int newY = y + dy[dir];

    // Check if the new coordinates are out of bounds
    if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
        return 'E'; // Out of bounds
    }

    // Check the content of the specified cell
    if (field[newX][newY] == '.') {
        return '.'; // Empty cell
    }
    else if (field[newX][newY] == fig) {
        return '*'; // Cell occupied by the player's figure
    }
    else {
        return 'A'; // Cell occupied by the opponent's figure
    }
}

char getCell(const char field[10][10], int x, int y, int ofs, int dir, char fig) {
    // Define directions
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

    // Calculate polar coordinates
    int newX = x + ofs * dx[dir];
    int newY = y + ofs * dy[dir];

    // Check if coordinates are out of bounds
    if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
        return 'E'; // Out of bounds
    }

    // Check the content of the specified cell
    if (field[newX][newY] == '.') {
        return '.'; // Empty cell
    }
    else if (field[newX][newY] == fig) {
        return '*'; // Cell occupied by the player's figure
    }
    else {
        return 'A'; // Cell occupied by the opponent's figure
    }
}


bool checkForPattern(const char field[10][10], int x, int y, int dir, const char* leftPattern, const char* rightPattern, char fig) {
    // Define directions
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

    // Iterate through all eight directions
    for (int i = 0; i < 8; ++i) {
        // Calculate coordinates for the current direction
        int newX = x;
        int newY = y;

        // Check the left part of the pattern
        for (int j = 0; leftPattern[j] != '\0'; ++j) {
            char cell = getCell(field, newX, newY, j + 1, (dir + i) % 8, fig);
            if (cell != leftPattern[j]) {
                break; // Pattern does not match
            }
            if (leftPattern[j + 1] == '\0') {
                // Left part of the pattern matched, check the right part
                for (int k = 0; rightPattern[k] != '\0'; ++k) {
                    char rightCell = getCell(field, newX, newY, k + 1, (dir + i + 4) % 8, fig);
                    if (rightCell != rightPattern[k]) {
                        break; // Pattern does not match
                    }
                    if (rightPattern[k + 1] == '\0') {
                        return true; // Both left and right parts of the pattern matched
                    }
                }
            }
        }
    }

    return false; // Pattern not found in any direction
}

bool searchForPattern(const char field[10][10], const char* leftPattern, const char* rightPattern, char fig, int& x, int& y) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            // Check if the cell is empty
            if (field[i][j] == '.') {
                // Check for the pattern around the empty cell
                if (checkForPattern(field, i, j, 0, leftPattern, rightPattern, fig)) {
                    x = i;
                    y = j;
                    return true;
                }
            }
        }
    }

    return false; // Pattern not found around any empty cell
}

bool search4(const char field[10][10], char fig, int& x, int& y) {
    // Define dangerous patterns for a "4 in a row" combination
    const char* leftPattern1 = "....";
    const char* rightPattern1 = ".*...";

    const char* leftPattern2 = "...*";
    const char* rightPattern2 = "....";

    const char* leftPattern3 = "...*.";
    const char* rightPattern3 = ".*...";

    const char* leftPattern4 = ".*...";
    const char* rightPattern4 = "...*.";

    const char* leftPattern5 = "....";
    const char* rightPattern5 = "...*.";

    const char* leftPattern6 = ".*...";
    const char* rightPattern6 = "....";

    const char* leftPattern7 = "...*.";
    const char* rightPattern7 = "...*.";

    const char* leftPattern8 = ".*...";
    const char* rightPattern8 = ".*...";

    const char* leftPattern9 = "....";
    const char* rightPattern9 = ".*..*";

    const char* leftPattern10 = ".*..*";
    const char* rightPattern10 = "....";

    const char* leftPattern11 = "...*.";
    const char* rightPattern11 = ".*..*";

    const char* leftPattern12 = ".*..*";
    const char* rightPattern12 = "...*.";

    const char* leftPattern13 = ".*...";
    const char* rightPattern13 = ".*..*";

    const char* leftPattern14 = ".*..*";
    const char* rightPattern14 = ".*...";

    const char* leftPattern15 = "...*.";
    const char* rightPattern15 = ".*...";

    const char* leftPattern16 = ".*...";
    const char* rightPattern16 = "...*.";

    const char* leftPattern17 = "....";
    const char* rightPattern17 = ".*.*.";

    const char* leftPattern18 = ".*.*.";
    const char* rightPattern18 = "....";

    const char* leftPattern19 = "...*.";
    const char* rightPattern19 = ".*.*.";

    const char* leftPattern20 = ".*.*.";
    const char* rightPattern20 = "...*.";

    // Call the searchForPattern function to find any dangerous combination
    if (searchForPattern(field, leftPattern1, rightPattern1, fig, x, y) ||
        searchForPattern(field, leftPattern2, rightPattern2, fig, x, y) ||
        searchForPattern(field, leftPattern3, rightPattern3, fig, x, y) ||
        searchForPattern(field, leftPattern4, rightPattern4, fig, x, y) ||
        searchForPattern(field, leftPattern5, rightPattern5, fig, x, y) ||
        searchForPattern(field, leftPattern6, rightPattern6, fig, x, y) ||
        searchForPattern(field, leftPattern7, rightPattern7, fig, x, y) ||
        searchForPattern(field, leftPattern8, rightPattern8, fig, x, y) ||
        searchForPattern(field, leftPattern9, rightPattern9, fig, x, y) ||
        searchForPattern(field, leftPattern10, rightPattern10, fig, x, y) ||
        searchForPattern(field, leftPattern11, rightPattern11, fig, x, y) ||
        searchForPattern(field, leftPattern12, rightPattern12, fig, x, y) ||
        searchForPattern(field, leftPattern13, rightPattern13, fig, x, y) ||
        searchForPattern(field, leftPattern14, rightPattern14, fig, x, y) ||
        searchForPattern(field, leftPattern15, rightPattern15, fig, x, y) ||
        searchForPattern(field, leftPattern16, rightPattern16, fig, x, y) ||
        searchForPattern(field, leftPattern17, rightPattern17, fig, x, y) ||
        searchForPattern(field, leftPattern18, rightPattern18, fig, x, y) ||
        searchForPattern(field, leftPattern19, rightPattern19, fig, x, y) ||
        searchForPattern(field, leftPattern20, rightPattern20, fig, x, y)) {
        return true;
    }

    return false;
}

bool search3(const char field[10][10], char fig, int& x, int& y) {
    // Define dangerous patterns for a "3 in a row" combination
    const char* leftPattern1 = "...";
    const char* rightPattern1 = "..*.";

    const char* leftPattern2 = "...*.";
    const char* rightPattern2 = "...";

    const char* leftPattern3 = "..*..";
    const char* rightPattern3 = "...";

    const char* leftPattern4 = "...";
    const char* rightPattern4 = "..*..";

    const char* leftPattern5 = "..*.";
    const char* rightPattern5 = "...*.";

    const char* leftPattern6 = "...*.";
    const char* rightPattern6 = "..*..";

    const char* leftPattern7 = "...";
    const char* rightPattern7 = "...*.";

    const char* leftPattern8 = "..*..";
    const char* rightPattern8 = "...*.";

    const char* leftPattern9 = "...*.";
    const char* rightPattern9 = "...*.";

    const char* leftPattern10 = "..*..";
    const char* rightPattern10 = "..*..";

    const char* leftPattern11 = "..*.";
    const char* rightPattern11 = "..*..";

    const char* leftPattern12 = "...*.";
    const char* rightPattern12 = "...*.";

    const char* leftPattern13 = "..*..";
    const char* rightPattern13 = "...*.";

    const char* leftPattern14 = "...*.";
    const char* rightPattern14 = "..*..";

    const char* leftPattern15 = "...";
    const char* rightPattern15 = "...*.";

    const char* leftPattern16 = "..*..";
    const char* rightPattern16 = "...*.";

    const char* leftPattern17 = "..*.";
    const char* rightPattern17 = "..*..";

    const char* leftPattern18 = "...*.";
    const char* rightPattern18 = "...*.";

    const char* leftPattern19 = "..*..";
    const char* rightPattern19 = "...*.";

    const char* leftPattern20 = "...*.";
    const char* rightPattern20 = "..*..";

    // Call the searchForPattern function to find any dangerous combination
    if (searchForPattern(field, leftPattern1, rightPattern1, fig, x, y) ||
        searchForPattern(field, leftPattern2, rightPattern2, fig, x, y) ||
        searchForPattern(field, leftPattern3, rightPattern3, fig, x, y) ||
        searchForPattern(field, leftPattern4, rightPattern4, fig, x, y) ||
        searchForPattern(field, leftPattern5, rightPattern5, fig, x, y) ||
        searchForPattern(field, leftPattern6, rightPattern6, fig, x, y) ||
        searchForPattern(field, leftPattern7, rightPattern7, fig, x, y) ||
        searchForPattern(field, leftPattern8, rightPattern8, fig, x, y) ||
        searchForPattern(field, leftPattern9, rightPattern9, fig, x, y) ||
        searchForPattern(field, leftPattern10, rightPattern10, fig, x, y) ||
        searchForPattern(field, leftPattern11, rightPattern11, fig, x, y) ||
        searchForPattern(field, leftPattern12, rightPattern12, fig, x, y) ||
        searchForPattern(field, leftPattern13, rightPattern13, fig, x, y) ||
        searchForPattern(field, leftPattern14, rightPattern14, fig, x, y) ||
        searchForPattern(field, leftPattern15, rightPattern15, fig, x, y) ||
        searchForPattern(field, leftPattern16, rightPattern16, fig, x, y) ||
        searchForPattern(field, leftPattern17, rightPattern17, fig, x, y) ||
        searchForPattern(field, leftPattern18, rightPattern18, fig, x, y) ||
        searchForPattern(field, leftPattern19, rightPattern19, fig, x, y) ||
        searchForPattern(field, leftPattern20, rightPattern20, fig, x, y)) {
        return true;
    }

    return false;
}

bool search2(const char field[10][10], char fig, int& x, int& y) {
    // Define dangerous patterns for a "2 in a row" combination
    const char* leftPattern1 = "..";
    const char* rightPattern1 = ".*.";

    const char* leftPattern2 = ".*.";
    const char* rightPattern2 = "..";

    const char* leftPattern3 = "...";
    const char* rightPattern3 = ".*.";

    const char* leftPattern4 = ".*.";
    const char* rightPattern4 = "...";

    const char* leftPattern5 = "..";
    const char* rightPattern5 = ".*.";

    const char* leftPattern6 = ".*.";
    const char* rightPattern6 = "..";

    const char* leftPattern7 = "..";
    const char* rightPattern7 = "...";

    const char* leftPattern8 = "...";
    const char* rightPattern8 = "..";

    // Call the searchForPattern function to find any dangerous combination
    if (searchForPattern(field, leftPattern1, rightPattern1, fig, x, y) ||
        searchForPattern(field, leftPattern2, rightPattern2, fig, x, y) ||
        searchForPattern(field, leftPattern3, rightPattern3, fig, x, y) ||
        searchForPattern(field, leftPattern4, rightPattern4, fig, x, y) ||
        searchForPattern(field, leftPattern5, rightPattern5, fig, x, y) ||
        searchForPattern(field, leftPattern6, rightPattern6, fig, x, y) ||
        searchForPattern(field, leftPattern7, rightPattern7, fig, x, y) ||
        searchForPattern(field, leftPattern8, rightPattern8, fig, x, y)) {
        return true;
    }

    return false;
}

bool searchR(const char field[10][10], char fig, int& x, int& y) {
    // Check if the center is available, if yes, place the figure there
    if (field[4][4] == '.') {
        x = 4;
        y = 4;
        return true;
    }

    // Iterate outward from the center to find the nearest available empty cell
    for (int radius = 1; radius <= 4; ++radius) {
        for (int i = 4 - radius; i <= 4 + radius; ++i) {
            for (int j = 4 - radius; j <= 4 + radius; ++j) {
                // Check if the cell is within the game board boundaries
                if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                    // Check if the cell is empty
                    if (field[i][j] == '.') {
                        x = i;
                        y = j;
                        return true;
                    }
                }
            }
        }
    }

    return false; // No available empty cell found
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " playerFigure source out" << std::endl;
        return 1;
    }

    char playerFigure = argv[1][0];
    char field[10][10];

    // Read the field from the source file
    if (!readField(argv[2], field)) {
        std::cerr << "Error reading the field from file: " << argv[2] << std::endl;
        return 1;
    }

    int bestMoveX = -1;
    int bestMoveY = -1;

    // Search for patterns and find the best move
    if (search4(field, playerFigure, bestMoveX, bestMoveY) ||
        search3(field, playerFigure, bestMoveX, bestMoveY) ||
        search2(field, playerFigure, bestMoveX, bestMoveY) ||
        searchR(field, playerFigure, bestMoveX, bestMoveY)) {
        // Save the best move to the output file
        if (!saveResult(argv[3], bestMoveX, bestMoveY)) {
            std::cerr << "Error saving the result to file: " << argv[3] << std::endl;
            return 1;
        }

        std::cout << "Best move: " << static_cast<char>('A' + bestMoveY) << bestMoveX << std::endl;
    }
    else {
        std::cerr << "No valid move found." << std::endl;
        return 1;
    }

    return 0;
}