// Includes the string library so std::string can be used.
#include <string>

// Includes utility functions for console output, input, and helpers.
#include "Utilities.h"

// Includes character class definitions for fighters.
#include "Character.h"

// Includes duel logic declarations.
#include "Duel.h"

// Allows use of standard library names without the std:: prefix.
using namespace std;

// Prints the main menu options to the screen.
static void PrintMainMenu()
{
    // Clears the console screen.
    ClearScreen();

    // Prints the game banner.
    PrintBanner();

    // Displays the option to start a duel.
    TypeOut("1 Start duel\n");

    // Displays the option to view saved statistics.
    TypeOut("2 View stats\n");

    // Displays the option to exit the application.
    TypeOut("3 Exit\n\n");
}

// Displays the statistics screen showing saved fighter records.
static void ShowStatsScreen()
{
    // Clears the console screen.
    ClearScreen();

    // Prints the game banner.
    PrintBanner();

    // Allocates an array to store stat records.
    StatRecord records[200];

    // Stores the number of loaded records.
    int count = 0;

    // Loads statistics from the stats file.
    LoadStats("fighter_stats.txt", records, &count);

    // Checks if no stats have been saved yet.
    if (count == 0)
    {
        // Informs the user that no stats exist.
        TypeOut("No saved stats yet.\n\n");

        // Waits for the user to press Enter.
        WaitForEnter();

        // Returns to the main menu.
        return;
    }

    // Prints a header for the stats list.
    TypeOut("Saved fighter stats\n\n");

    // Iterates through all loaded records.
    for (int i = 0; i < count; ++i)
    {
        // Prints the fighter name, win count, and loss count.
        TypeOut(
            records[i].name +
            "  wins " + to_string(records[i].wins) +
            "  losses " + to_string(records[i].losses) +
            "\n"
        );
    }

    // Prints a blank line for spacing.
    TypeOut("\n");

    // Waits for the user to press Enter before returning.
    WaitForEnter();
}

// Entry point of the application.
int main()
{
    // Seeds the random number generator.
    SeedRng();

    // Controls whether the main loop continues running.
    bool running = true;

    // Runs the main menu loop until the user chooses to exit.
    while (running)
    {
        // Displays the main menu.
        PrintMainMenu();

        // Reads the user's menu selection.
        int menuChoice = ReadIntChoice("Choice 1 3: ", 1, 3);

        // Checks if the user selected the exit option.
        if (menuChoice == 3)
        {
            // Sets the running flag to false to exit the loop.
            running = false;

            // Breaks out of the loop.
            break;
        }

        // Checks if the user selected the stats screen option.
        if (menuChoice == 2)
        {
            // Displays the stats screen.
            ShowStatsScreen();

            // Returns to the main menu loop.
            continue;
        }

        // Clears the screen before starting a duel.
        ClearScreen();

        // Prints the game banner.
        PrintBanner();

        // Prompts the user to choose a difficulty level.
        int difficulty = ChooseDifficulty();

        // Prompts for the fighter class of the first slot.
        TypeOut("\nChoose fighter class for slot A\n");

        // Reads the class choice for fighter A.
        int aClass = ChooseFighterClass();

        // Prompts for the fighter class of the second slot.
        TypeOut("\nChoose fighter class for slot B\n");

        // Reads the class choice for fighter B.
        int bClass = ChooseFighterClass();

        // Prompts the user to enter a name for fighter A.
        string aName = ReadLine("\nEnter name for fighter A: ");

        // Prompts the user to enter a name for fighter B.
        string bName = ReadLine("Enter name for fighter B: ");

        // Ensures the two fighter names are not identical.
        ValidateDistinctNames(&aName, &bName);

        // Creates default fighter objects used as storage for factory creation.
        Ninja defaultA("A");
        Pirate defaultB("B");
        Samurai defaultC("C");
        Viking defaultD("D");

        // Creates the first fighter based on the selected class and name.
        Character* a = CreateFighter(
            aClass,
            aName,
            &defaultA,
            &defaultB,
            &defaultC,
            &defaultD
        );

        // Creates the second fighter based on the selected class and name.
        Character* b = CreateFighter(
            bClass,
            bName,
            &defaultA,
            &defaultB,
            &defaultC,
            &defaultD
        );

        // Starts the duel between the two fighters.
        Duel(a, b, &difficulty);

        // Prints a blank line after the duel ends.
        TypeOut("\n");

        // Waits for the user before returning to the menu.
        WaitForEnter("Press Enter to return to the menu.");
    }

    // Returns zero to indicate successful program termination.
    return 0;
}