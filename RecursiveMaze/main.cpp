#include <iostream>              // Includes input and output tools for printing to the screen
#include <vector>                // Includes the vector container for storing the maze
#include <random>                // Includes random number utilities for generating walls and paths

using namespace std;             // Uses the standard namespace to avoid prefixing std everywhere

void fillMaze(vector<string>& maze,   // Reference to the maze grid
    int row,                // Current row index
    int col,                // Current column index
    int size,               // Size of the maze
    default_random_engine& engine,          // Random engine used for number generation
    uniform_int_distribution<int>& dist) { // Random distribution for wall or path choice
    if (row == size) {                // Checks if we reached the end of the maze grid
        return;                       // Stops the recursion when all rows are processed
    }

    if (row == 0 || col == 0 || row == size - 1 || col == size - 1) {
        // Checks if the current cell is on the outer border
        maze[row][col] = '#';        // Sets border cells as walls to form the maze boundary
    }
    else {                            // Handles all inner cells
        int value = dist(engine);     // Generates a random number for cell type selection
        if (value == 0) {             // Checks if we should place a wall
            maze[row][col] = '#';     // Places a wall
        }
        else {                        // Otherwise place an open path
            maze[row][col] = ' ';     // Places a path
        }
    }

    int nextRow = row;                // Stores the next row to visit
    int nextCol = col + 1;            // Moves one step to the right within the same row

    if (nextCol == size) {            // Checks if we reached the end of the row
        nextCol = 0;                  // Resets the column to the first position
        nextRow++;                    // Moves down to the next row
    }

    fillMaze(maze, nextRow, nextCol, size, engine, dist);
    // Recursively processes the next cell in row major order
}

void generateMaze(int size) {
    vector<string> maze(size, string(size, '#'));
    // Creates a square maze filled with walls

    random_device rd;                 // Creates a random device for seeding the engine
    default_random_engine engine(rd());
    // Creates the engine seeded with random hardware data

    uniform_int_distribution<int> dist(0, 3);
    // Creates a distribution that will generate values from zero to three

    fillMaze(maze, 0, 0, size, engine, dist);
    // Begins recursion at cell zero comma zero

    for (int r = 0; r < size; ++r) {  // Loops through each row of the maze
        cout << maze[r] << '\n';      // Prints each row to the console
    }
}

int main() {
    int size;                         // Stores the maze size chosen by the user

    cout << "Enter maze size (for example 30 for a 30 x 30 maze): ";
    // Prompts the user to enter a size
    cin >> size;                      // Reads the size from user input

    if (size < 3) {                   // Checks for an invalid size
        cout << "Size must be 3 or larger.\n";
        // Prints an error message
        return 0;                     // Exits the program early
    }

    generateMaze(size);               // Generates and displays the maze

    cout << "\nPress Enter to exit."; // Prompts the user before closing
    cin.ignore();                     // Clears leftover input from the buffer
    cin.get();                        // Waits for the user to press Enter
    return 0;                         // Ends the program
}