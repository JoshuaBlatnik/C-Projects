// Includes the header that declares all utility functions and structs used in this file.
#include "Utilities.h"

// Includes standard input and output streams for console printing and reading.
#include <iostream>

// Includes time utilities used for sleeps and timing operations.
#include <chrono>

// Includes threading utilities used for sleeping the current thread.
#include <thread>

// Includes string stream utilities used for formatted string building.
#include <sstream>

// Includes formatting utilities such as setw and alignment flags.
#include <iomanip>

// Includes file stream utilities used to read and write stats files.
#include <fstream>

// Includes C time utilities used for seeding the random number generator.
#include <ctime>

// Includes standard utilities including system calls and rand usage.
#include <cstdlib>

// Includes Windows console support only when compiling on Windows.
#ifdef _WIN32
#include <windows.h>
#endif

// Allows use of standard library names without the std:: prefix.
using namespace std;

// Sets the console text color on Windows platforms.
void SetColor(int attr)
{
#ifdef _WIN32
    // Retrieves the handle for standard output on Windows.
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Applies the requested color attribute to the console.
    SetConsoleTextAttribute(h, static_cast<WORD>(attr));
#else
    // Suppresses unused parameter warnings on non-Windows platforms.
    (void)attr;
#endif
}

// Pauses the current thread for a specified number of milliseconds.
void PauseMs(int ms)
{
    // Sleeps the current thread for the provided duration.
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Prints text one character at a time with a delay to create a typing effect.
void TypeOut(const string& s, int perCharMs)
{
    // Loops through every character in the string.
    for (char c : s)
    {
        // Prints the character immediately without buffering.
        cout << c << flush;

        // Delays before printing the next character.
        this_thread::sleep_for(chrono::milliseconds(perCharMs));
    }
}

// Displays a prompt and waits until the user presses Enter.
void WaitForEnter(const string& prompt)
{
    // Prints the provided prompt.
    TypeOut(prompt);

    // Stores the user input line so the Enter press is consumed.
    string _;

    // Reads an entire line to wait for Enter.
    getline(cin, _);
}

// Clears the console screen using an operating system specific command.
void ClearScreen()
{
#ifdef _WIN32
    // Clears the screen on Windows systems.
    system("cls");
#else
    // Clears the screen on non-Windows systems.
    system("clear");
#endif
}

// Prints the main banner header for the game.
void PrintBanner()
{
#ifdef _WIN32
    // Sets the banner color on Windows systems.
    SetColor(11);
#endif
    // Prints a leading blank line for spacing.
    TypeOut("\n");

    // Prints the top border of the banner.
    TypeOut("========================================\n", 2);

    // Prints the banner title line.
    TypeOut(" NINJA VERSUS PIRATE DUEL ARENA\n", 2);

    // Prints the bottom border of the banner.
    TypeOut("========================================\n\n", 2);
#ifdef _WIN32
    // Restores the default console color on Windows systems.
    SetColor(7);
#endif
}

// Seeds the random number generator using the current time.
void SeedRng()
{
    // Seeds rand using the current epoch time.
    srand(static_cast<unsigned int>(time(nullptr)));
}

// Returns a random integer in the inclusive range [minValue, maxValue].
int RngInt(int minValue, int maxValue)
{
    // Swaps the bounds if they were provided in reverse order.
    if (maxValue < minValue)
    {
        // Stores the original minimum temporarily.
        int t = minValue;

        // Moves the larger value into the minimum position.
        minValue = maxValue;

        // Restores the smaller value into the maximum position.
        maxValue = t;
    }

    // Computes the size of the inclusive range.
    int span = (maxValue - minValue) + 1;

    // Ensures the span never becomes zero or negative.
    if (span <= 0) span = 1;

    // Returns a random number mapped into the requested range.
    return minValue + (rand() % span);
}

// Returns a random floating point value in the range [0.0, 1.0].
double RngUnit()
{
    // Converts rand output into a normalized double value.
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

// Attempts to parse an integer from a string without throwing exceptions.
static bool TryParseInt(const string& text, int* outValue)
{
    // Rejects empty strings immediately.
    if (text.empty()) return false;

    // Stores the sign multiplier for negative numbers.
    int sign = 1;

    // Tracks the index of the first digit to read.
    size_t i = 0;

    // Skips a leading plus sign if present.
    if (text[0] == '+') i = 1;
    // Detects a leading minus sign and updates the sign multiplier.
    else if (text[0] == '-') { sign = -1; i = 1; }

    // Rejects input that is only a sign with no digits.
    if (i >= text.size()) return false;

    // Uses a wide type to safely accumulate digits.
    long long value = 0;

    // Reads and validates each character as a digit.
    for (; i < text.size(); ++i)
    {
        // Reads the current character.
        char c = text[i];

        // Rejects non-digit characters.
        if (c < '0' || c > '9') return false;

        // Shifts the current value and adds the digit.
        value = value * 10 + (c - '0');

        // Rejects values that exceed a safe bound for this app.
        if (value > 2000000000LL) return false;
    }

    // Writes the parsed integer value to the output pointer.
    *outValue = static_cast<int>(value * sign);

    // Returns true to indicate parsing succeeded.
    return true;
}

// Reads a full line of input and provides a default value if the line is empty.
string ReadLine(const string& prompt)
{
    // Displays the prompt message.
    TypeOut(prompt);

    // Stores the line the user enters.
    string s;

    // Reads the full line of input.
    getline(cin, s);

    // Applies a default value when the user enters nothing.
    if (s.empty()) s = "Player";

    // Returns the final string.
    return s;
}

// Reads an integer choice within an inclusive range, retrying up to a fixed attempt limit.
int ReadIntChoice(const string& prompt, int min, int max)
{
    // Tracks how many attempts the user has made.
    int attempts = 0;

    // Defines the maximum number of allowed attempts.
    const int maxAttempts = 5;

    // Repeats until the attempt limit is reached.
    while (attempts < maxAttempts)
    {
        // Increments the attempt counter.
        attempts++;

        // Displays the input prompt.
        TypeOut(prompt);

        // Stores the user input line.
        string line;

        // Reads the full line.
        getline(cin, line);

        // Stores the parsed integer value.
        int value = 0;

        // Rejects non-numeric input.
        if (!TryParseInt(line, &value))
        {
            // Notifies the user that parsing failed.
            TypeOut("Invalid input.\n");

            // Continues to the next attempt.
            continue;
        }

        // Rejects values outside the allowed range.
        if (value < min || value > max)
        {
            // Notifies the user the value was out of range.
            TypeOut("Out of range.\n");

            // Continues to the next attempt.
            continue;
        }

        // Returns the validated choice.
        return value;
    }

    // Returns the minimum value as a safe fallback after too many failed attempts.
    return min;
}

// Builds a proportional ASCII health bar for a given health and maximum health.
string HealthBar(int hp, int maxHp)
{
    // Defines the total width of the bar.
    const int width = 24;

    // Prevents division by zero and negative max values.
    if (maxHp <= 0) maxHp = 1;

    // Clamps health to a non-negative value.
    if (hp < 0) hp = 0;

    // Clamps health to not exceed the maximum.
    if (hp > maxHp) hp = maxHp;

    // Computes how many characters should be filled based on the percentage.
    int filled = static_cast<int>((static_cast<double>(hp) / static_cast<double>(maxHp)) * width);

    // Clamps filled to the valid range.
    if (filled < 0) filled = 0;

    // Clamps filled to the bar width.
    if (filled > width) filled = width;

    // Starts the bar with an opening bracket.
    string bar = "[";

    // Adds filled segments using hash characters.
    bar.append(filled, '#');

    // Adds unfilled segments using dot characters.
    bar.append(width - filled, '.');

    // Ends the bar with a closing bracket.
    bar += "]";

    // Returns the completed bar string.
    return bar;
}

// Pads text to a fixed width on the left for clean alignment.
string PadLeft(const string& text, int w)
{
    // Creates a string stream to build formatted output.
    ostringstream oss;

    // Formats the text with a fixed width and left alignment.
    oss << setw(w) << left << text;

    // Returns the formatted string.
    return oss.str();
}

// Pads a number to a fixed width on the right for clean alignment.
string PadRightNumber(int value, int w)
{
    // Creates a string stream to build formatted output.
    ostringstream oss;

    // Formats the number with a fixed width and right alignment.
    oss << setw(w) << right << value;

    // Returns the formatted string.
    return oss.str();
}

// Displays the difficulty menu and returns the selected value.
int ChooseDifficulty()
{
    // Prints the difficulty heading.
    TypeOut("Difficulty\n");

    // Prints the training option.
    TypeOut("1 Training\n");

    // Prints the standard option.
    TypeOut("2 Standard\n");

    // Prints the high risk option.
    TypeOut("3 High risk\n\n");

    // Reads and returns a validated difficulty choice.
    return ReadIntChoice("Choose 1 3: ", 1, 3);
}

// Displays the fighter class menu and returns the selected value.
int ChooseFighterClass()
{
    // Prints the ninja option.
    TypeOut("1 Ninja\n");

    // Prints the pirate option.
    TypeOut("2 Pirate\n");

    // Prints the samurai option.
    TypeOut("3 Samurai\n");

    // Prints the viking option.
    TypeOut("4 Viking\n\n");

    // Reads and returns a validated class choice.
    return ReadIntChoice("Choose 1 4: ", 1, 4);
}

// Loads stat records from a file into an array.
void LoadStats(const string& path, StatRecord* outRecords, int* outCount)
{
    // Resets the output count to zero before loading.
    *outCount = 0;

    // Opens the input file for reading.
    ifstream in(path.c_str());

    // Exits early if the file is not readable.
    if (!in.good()) return;

    // Stores each line read from the file.
    string line;

    // Reads lines until the file ends.
    while (getline(in, line))
    {
        // Skips empty lines.
        if (line.empty()) continue;

        // Stops if the record array is full.
        if (*outCount >= 200) break;

        // Finds the first delimiter position.
        size_t p1 = line.find('|');

        // Initializes the second delimiter position.
        size_t p2 = string::npos;

        // Finds the second delimiter if the first delimiter was found.
        if (p1 != string::npos) p2 = line.find('|', p1 + 1);

        // Skips malformed lines that do not contain both delimiters.
        if (p1 == string::npos || p2 == string::npos) continue;

        // Extracts the name field.
        string name = line.substr(0, p1);

        // Extracts the wins field text.
        string wText = line.substr(p1 + 1, p2 - (p1 + 1));

        // Extracts the losses field text.
        string lText = line.substr(p2 + 1);

        // Stores parsed wins.
        int w = 0;

        // Stores parsed losses.
        int l = 0;

        // Parses wins text or defaults to zero.
        if (!TryParseInt(wText, &w)) w = 0;

        // Parses losses text or defaults to zero.
        if (!TryParseInt(lText, &l)) l = 0;

        // Writes the parsed name into the record.
        outRecords[*outCount].name = name;

        // Writes the parsed wins into the record.
        outRecords[*outCount].wins = w;

        // Writes the parsed losses into the record.
        outRecords[*outCount].losses = l;

        // Increments the record count.
        (*outCount)++;
    }
}

// Saves stat records to a file in a simple delimiter format.
void SaveStats(const string& path, const StatRecord* records, int count)
{
    // Opens the output file and truncates existing content.
    ofstream out(path.c_str(), ios::trunc);

    // Exits early if the file is not writable.
    if (!out.good()) return;

    // Writes each record line to the file.
    for (int i = 0; i < count; ++i)
    {
        // Writes the name, wins, and losses separated by delimiters.
        out << records[i].name << "|" << records[i].wins << "|" << records[i].losses << "\n";
    }
}

// Finds the index of a stat record matching a name.
int FindStatIndex(const StatRecord* records, int count, const string& name)
{
    // Loops through each record in the array.
    for (int i = 0; i < count; ++i)
    {
        // Returns the index when the name matches.
        if (records[i].name == name) return i;
    }

    // Returns -1 to indicate the name was not found.
    return -1;
}

// Updates a stat record by adding a win or a loss and saving back to disk.
static void BumpStat(const string& path, const string& name, bool isWin)
{
    // Allocates a fixed array for stat records.
    StatRecord records[200];

    // Stores the number of loaded records.
    int count = 0;

    // Loads existing records from disk.
    LoadStats(path, records, &count);

    // Looks up the existing record index for the name.
    int idx = FindStatIndex(records, count, name);

    // Creates a new record if the name does not already exist.
    if (idx == -1)
    {
        // Exits if the record array is already full.
        if (count >= 200) return;

        // Sets the new index to the end of the list.
        idx = count;

        // Stores the new name.
        records[idx].name = name;

        // Initializes wins to zero.
        records[idx].wins = 0;

        // Initializes losses to zero.
        records[idx].losses = 0;

        // Increments the record count.
        count++;
    }

    // Increments wins if the update is a win.
    if (isWin) records[idx].wins += 1;

    // Increments losses if the update is a loss.
    else records[idx].losses += 1;

    // Saves the updated records back to disk.
    SaveStats(path, records, count);
}

// Adds one win to a fighter record and saves the stats file.
void AddWin(const string& path, const string& name)
{
    // Calls the shared update function with the win flag set to true.
    BumpStat(path, name, true);
}

// Adds one loss to a fighter record and saves the stats file.
void AddLoss(const string& path, const string& name)
{
    // Calls the shared update function with the win flag set to false.
    BumpStat(path, name, false);
}