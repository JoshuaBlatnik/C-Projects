// Ensures this header file is only included once during compilation.
#pragma once

// Includes the string library so std::string can be used.
#include <string>

// Sets the console text color using a platform specific implementation.
void SetColor(int attr);

// Pauses execution for a specified number of milliseconds.
void PauseMs(int ms);

// Outputs text to the console one character at a time to simulate typing.
// The per character delay defaults to 12 milliseconds.
void TypeOut(const std::string& s, int perCharMs = 12);

// Displays a prompt and waits for the user to press Enter.
// A default prompt is provided if none is specified.
void WaitForEnter(const std::string& prompt = "Press Enter to continue.");

// Clears the console screen using an operating system specific command.
void ClearScreen();

// Prints the main game banner and title.
void PrintBanner();

// Seeds the random number generator using the current system time.
void SeedRng();

// Returns a random integer between the given minimum and maximum values inclusive.
int RngInt(int minValue, int maxValue);

// Returns a random floating point value between 0.0 and 1.0.
double RngUnit();

// Displays a prompt and reads an entire line of text input from the user.
std::string ReadLine(const std::string& prompt);

// Displays a prompt and reads an integer choice within a specified range.
int ReadIntChoice(const std::string& prompt, int min, int max);

// Builds and returns an ASCII health bar based on current and maximum health.
std::string HealthBar(int hp, int maxHp);

// Pads text to a fixed width for aligned output.
std::string PadLeft(const std::string& text, int w);

// Pads a number to a fixed width for aligned numeric output.
std::string PadRightNumber(int value, int w);

// Displays the difficulty selection menu and returns the chosen value.
int ChooseDifficulty();

// Displays the fighter class selection menu and returns the chosen value.
int ChooseFighterClass();

// Defines a structure used to store persistent win and loss statistics.
struct StatRecord
{
    // Stores the fighter name associated with the record.
    std::string name;

    // Stores the total number of wins.
    int wins;

    // Stores the total number of losses.
    int losses;
};

// Loads fighter statistics from a file into an array of records.
void LoadStats(const std::string& path, StatRecord* outRecords, int* outCount);

// Saves fighter statistics from an array of records to a file.
void SaveStats(const std::string& path, const StatRecord* records, int count);

// Finds and returns the index of a fighter record by name or -1 if not found.
int FindStatIndex(const StatRecord* records, int count, const std::string& name);

// Increments the win count for a fighter and saves the updated stats.
void AddWin(const std::string& path, const std::string& name);

// Increments the loss count for a fighter and saves the updated stats.
void AddLoss(const std::string& path, const std::string& name);