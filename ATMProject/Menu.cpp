#include "Menu.h" // include header for menu declarations
#include <iostream> // include input and output stream library
#include <limits> // include numeric limits for input validation

namespace atmapp { // begin atmapp namespace

    void ShowMenu(std::ostream& out) { // display ATM options menu
        out << "\n============================\n"; // top border
        out << " 1. View balances\n"; // option 1
        out << " 2. Deposit\n"; // option 2
        out << " 3. Withdraw\n"; // option 3
        out << " 4. Transfer\n"; // option 4
        out << " 5. Credit score\n"; // option 5
        out << " 6. Purchases\n"; // option 6
        out << " 7. Paychecks\n"; // option 7
        out << " 8. Regenerate history\n"; // option 8
        out << " 9. Exit\n"; // option 9
        out << "============================\n"; // bottom border
    } // end ShowMenu

    int ReadMenuChoice(std::istream& in, std::ostream& out) { // read and validate user’s menu selection
        int choice{}; // variable to hold menu option
        out << " Select option. "; // prompt user for input
        while (!(in >> choice) || choice < 1 || choice > 9) { // validate range and type
            out << " Enter number 1 to 9. "; // prompt correction
            in.clear(); // clear input flags
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        } // repeat until valid input
        return choice; // return validated option
    } // end ReadMenuChoice

}