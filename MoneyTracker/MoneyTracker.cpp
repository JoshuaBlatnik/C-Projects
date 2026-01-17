// This program tracks simple money transactions and saves them to a text file.

#include <iostream>      // Includes the input and output stream library for user interaction.
#include <fstream>       // Includes the file stream library for reading and writing files.
#include <string>        // Includes the string library for handling text.
#include <iomanip>       // Includes the iomanip library for formatting numerical output.
#include <sstream>       // Includes the string stream library for formatting text into strings.

using namespace std;     // Allows the use of standard library names without the std prefix.

// This function writes the same text to the screen and to the file.
void WriteToScreenAndFile(const string& text, ofstream& fileOut) {
    cout << text;        // Writes the text to the screen.
    fileOut << text;     // Writes the same text to the file.
}

int main() {             // The main function begins the program.

    ofstream moneyFile("money_log.txt");   // Opens a file named money_log.txt for writing.

    if (!moneyFile) {                      // Checks if the file failed to open.
        cout << "Error opening money_log.txt for writing." << endl;   // Displays an error message.
        return 1;                          // Ends the program with an error code.
    }

    cout << fixed << setprecision(2);      // Formats money values on the screen to two decimals.
    moneyFile << fixed << setprecision(2); // Formats money values in the file similarly.

    cout << "Money Tracker" << endl;       // Displays the program title.
    cout << "Track your income and expenses." << endl;                // Brief program description.
    cout << "Everything is saved to money_log.txt as you enter it." << endl; // File explanation.
    cout << "At the end, your file will be read back to you." << endl;        // Final output note.
    cout << endl;                          // Prints a blank line for readability.

    moneyFile << "Money Tracker" << endl;  // Writes the title to the file.
    moneyFile << "Session log" << endl << endl;  // Writes a header into the file.

    cout << "Enter your name: ";           // Prompts the user to enter their name.
    string userName;                       // Declares a string variable for the user's name.
    getline(cin, userName);                // Reads the user's name as a full line.

    if (userName.empty()) {                // Checks if the user left the name blank.
        userName = "Guest";                // Assigns a default name.
    }

    cout << "Enter your starting balance: ";  // Prompts for the starting balance.
    double balance = 0.0;                  // Initializes the balance variable.
    cin >> balance;                        // Reads the user's starting balance.

    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Clears leftover input characters.

    string header = "\nMoney session for " + userName + "\n";   // Builds a session header.
    WriteToScreenAndFile(header, moneyFile);                    // Writes the header to both outputs.

    string startLine = "Starting balance: $" + to_string(balance) + "\n\n";  // Formats balance line.
    WriteToScreenAndFile(startLine, moneyFile);                              // Outputs the line.

    cout << left << setw(12) << "Type"          // Displays column headers on the screen.
        << left << setw(20) << "Description"
        << right << setw(12) << "Amount"
        << right << setw(14) << "New balance" << endl;
    cout << string(58, '=') << endl;            // Prints a divider line.

    moneyFile << left << setw(12) << "Type"     // Writes the same column headers to the file.
        << left << setw(20) << "Description"
        << right << setw(12) << "Amount"
        << right << setw(14) << "New balance" << endl;
    moneyFile << string(58, '=') << endl;       // Writes the divider to the file.

    bool running = true;                        // Controls the program loop.

    while (running) {                           // Begins a loop that continues until the user exits.

        cout << endl;                           // Prints a blank line before the menu.
        cout << "Menu:" << endl;                // Displays the menu title.
        cout << "1. Add income" << endl;        // Menu option for adding income.
        cout << "2. Add expense" << endl;       // Menu option for adding an expense.
        cout << "3. Finish and show file contents" << endl;   // Menu option to end the session.
        cout << endl;                           // Adds a blank line before input.

        cout << "Enter your choice (1 to 3): "; // Prompts the user to select a menu option.
        int choice;                             // Declares a variable to store the choice.
        cin >> choice;                          // Reads the user's menu choice.

        cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Clears leftover characters.

        if (choice == 1) {                      // Checks if the user chose to add income.

            cout << "Enter income description: ";  // Prompts for an income description.
            string description;                   // Declares a variable for the description.
            getline(cin, description);            // Reads the description.

            if (description.empty()) description = "Income";   // Assigns a default description.

            cout << "Enter amount: ";         // Prompts for the income amount.
            double amount;                    // Declares an amount variable.
            cin >> amount;                    // Reads the amount entered.

            cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Clears leftover input.

            balance += amount;                // Adds the income to the balance.

            ostringstream rowStream;          // Creates a stream to format the output row.
            rowStream << left << setw(12) << "Income"    // Formats the income row.
                << left << setw(20) << description
                << right << setw(12) << amount
                << right << setw(14) << balance << endl;

            WriteToScreenAndFile(rowStream.str(), moneyFile);   // Writes the row to both outputs.
        }
        else if (choice == 2) {               // Checks if the user chose to add an expense.

            cout << "Enter expense description: ";  // Prompts for a description.
            string description;                    // Declares a description variable.
            getline(cin, description);             // Reads the description.

            if (description.empty()) description = "Expense";   // Assigns a default description.

            cout << "Enter amount: ";         // Prompts for the expense amount.
            double amount;                    // Declares an amount variable.
            cin >> amount;                    // Reads the amount.

            cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Clears leftover characters.

            balance -= amount;                // Subtracts the expense from the balance.

            ostringstream rowStream;          // Creates a formatted row for output.
            rowStream << left << setw(12) << "Expense"  // Formats the expense row.
                << left << setw(20) << description
                << right << setw(12) << amount
                << right << setw(14) << balance << endl;

            WriteToScreenAndFile(rowStream.str(), moneyFile);   // Outputs the row.
        }
        else if (choice == 3) {               // Checks if the user chose to exit.

            cout << endl;                     // Prints a blank line for spacing.
            cout << "Reading saved file..." << endl << endl;  // Informs the user.
            running = false;                  // Ends the loop.
        }
        else {                                // Handles invalid menu choices.

            cout << "Invalid choice. Try again." << endl;   // Displays an error message.
        }
    }

    moneyFile.close();                        // Closes the output file.

    ifstream moneyRead("money_log.txt");      // Opens the file for reading.

    if (!moneyRead) {                         // Checks if the file failed to open.
        cout << "Error opening money_log.txt for reading." << endl;  // Displays an error.
        return 1;                             // Returns an error code.
    }

    cout << "========== Saved Money Log ==========" << endl << endl;   // Displays header.

    string line;                              // Declares a variable to hold each file line.
    while (getline(moneyRead, line)) {        // Reads the file line by line.
        cout << line << endl;                 // Prints each line to the screen.
    }

    moneyRead.close();                        // Closes the input file.

    cout << endl;                             // Prints a blank line for spacing.
    cout << "Thank you, " << userName << "." << endl;  // Displays a farewell message.

    return 0;                                 // Ends the program successfully.
}