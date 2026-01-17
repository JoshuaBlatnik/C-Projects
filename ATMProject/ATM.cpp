#include "ATM.h" // include ATM function declarations
#include "Menu.h" // include menu display and input helpers
#include "Transaction.h" // include transaction log functions
#include "Finance.h" // include finance log definitions
#include "Credit.h" // include credit profile definitions
#include "DataGen.h"  // include data gen definitions

#include <iostream> // include input and output stream library
#include <iomanip> // include formatting manipulators
#include <limits> // include numeric limits for input validation
#include <string> // include string utilities
#include <ctime> // include time utilities for timestamp generation

namespace atmapp { // begin atmapp namespace

    static void clearLine(std::istream& in) { // helper to clear input stream
        in.clear(); // clear any error flags
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore rest of input line
    } // end clearLine

    static std::string nowStamp() { // generate timestamp string
        std::time_t t = std::time(nullptr); // get current time
        std::tm localTime{}; // structure for local time data
#if defined(_WIN32)
        localtime_s(&localTime, &t); // convert to local time on Windows
#else
        localtime_r(&t, &localTime); // convert to local time on other systems
#endif
        char buf[32]; // buffer to hold formatted date
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime); // format date and time
        return std::string(buf); // return formatted timestamp
    } // end nowStamp

    void ShowBanner(std::ostream& out) { // display welcome banner
        out << "\n ============================================\n"; // top border
        out << "             Welcome to Garcia Bank\n"; // title line
        out << " ============================================\n"; // bottom border
        out << " Assistant. I can show balances, make moves, and build a personal finance view.\n"; // assistant message
    } // end ShowBanner

    bool SignIn(std::istream& in, std::ostream& out, const Account& probe) { // sign in function for account
        out << "\n Card detected. " << probe.card() << "\n"; // show detected card
        out << " Hello " << probe.owner() << "\n"; // greet user
        out << " Enter your pin.\n"; // ask for pin
        int tries = 0; // track failed attempts
        while (tries < 3) { // allow up to three tries
            out << " Pin. "; // prompt for pin
            int pin{}; // variable for entered pin
            if (in >> pin) { // check valid input
                if (probe.checkPin(pin)) { // verify pin
                    out << " Verified\n"; // success message
                    return true; // authentication success
                }
                else { // incorrect pin
                    ++tries; // increment try count
                    out << " Incorrect. Attempts left. " << (3 - tries) << "\n"; // warn user
                }
            }
            else { // invalid input type
                out << " Invalid input. Numbers only\n"; // prompt correction
                clearLine(in); // clear input line
            }
        }
        out << " Session locked. Contact support\n"; // after 3 failed attempts
        return false; // authentication failed
    } // end SignIn

    void RunSession(std::istream& in, std::ostream& out, Account& active, Account& savings, TransactionLog* log, FinanceLog* fin, CreditProfile* credit) { // main interactive session
        out << std::fixed << std::setprecision(2); // format monetary values with two decimals
        bool running = true; // control session loop
        while (running) { // continue until user exits
            ShowMenu(out); // display main menu
            int choice = ReadMenuChoice(in, out); // read user menu selection
            switch (choice) { // perform based on menu choice
            case 1: DoBalance(out, active, savings); break; // show balances
            case 2: DoDeposit(in, out, active, log); break; // deposit money
            case 3: DoWithdraw(in, out, active, log); break; // withdraw money
            case 4: DoTransfer(in, out, active, savings, log); break; // transfer funds
            case 5: // view credit score
                if (credit && fin) { // ensure both logs exist
                    double inc = fin->monthlyIncomeEstimate(); // calculate income
                    double spend = fin->monthlySpendEstimate(); // calculate spending
                    credit->compute(active.getBalance(), savings.getBalance(), inc, spend); // compute credit score
                    credit->print(out); // display score
                }
                else { // missing dependencies
                    out << "\nAssistant. Credit view not available.\n"; // error message
                }
                break;
            case 6: // view purchase history
                if (fin) fin->printPurchases(out, 25); // print purchases
                else out << "\nAssistant. No purchase log available.\n"; // missing finance log
                break;
            case 7: // view paychecks
                if (fin) fin->printPaychecks(out, 25); // print paychecks
                else out << "\nAssistant. No paycheck log available.\n"; // missing finance log
                break;
            case 8:
                if (fin) {
                    DataGen regen;
                    auto newHistory = regen.generateQuarterHistory(18, 2);
                    fin->set(std::move(newHistory));
                    out << "\nAssistant. Transaction history has been regenerated with new random purchases and paychecks.\n";
                }
                else {
                    out << "\nAssistant. History system not available.\n";
                }
                break;
            case 9: // exit session
                running = false; // set loop exit flag
                out << " Thank you. Goodbye\n"; // farewell message
                if (log) log->print(out); // print transaction log if exists
                break;
            } // end switch
        } // end while
    } // end RunSession

    void DoBalance(std::ostream& out, const Account& checking, const Account& savings) { // display balances for checking and savings
        out << " Checking balance. $" << checking.getBalance() << "\n"; // print checking balance
        out << " Savings balance.  $" << savings.getBalance() << "\n"; // print savings balance
    } // end DoBalance

    double ReadMoney(std::istream& in, std::ostream& out, const char* prompt, double minVal, double maxVal) { // read monetary input within range
        out << prompt; // show prompt message
        double v{}; // variable for value
        while (true) { // loop until valid input
            if (in >> v && v >= minVal && v <= maxVal) return v; // return valid value
            out << " Enter amount between " << minVal << " and " << maxVal << ". "; // prompt correction
            in.clear(); // clear error flags
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard rest of input line
        }
    } // end ReadMoney

    int ReadInt(std::istream& in, std::ostream& out, const char* prompt, int minVal, int maxVal) { // read integer input within range
        out << prompt; // show prompt message
        int v{}; // variable for value
        while (true) { // loop until valid input
            if (in >> v && v >= minVal && v <= maxVal) return v; // return valid value
            out << " Enter number between " << minVal << " and " << maxVal << ". "; // prompt correction
            in.clear(); // clear error flags
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        }
    } // end ReadInt

    void DoDeposit(std::istream& in, std::ostream& out, Account& acct, TransactionLog* log) { // deposit function
        double amt = ReadMoney(in, out, " Deposit amount. ", 0.01, 1000000.0); // read deposit amount
        if (acct.deposit(amt)) { // try deposit
            out << " Deposited. $" << amt << "\n New balance. $" << acct.getBalance() << "\n"; // confirm new balance
            if (log) log->logDeposit(acct.card(), amt, acct.getBalance(), nowStamp()); // log deposit
        }
        else { // deposit failed
            out << " Deposit failed\n"; // show error
        }
    } // end DoDeposit

    void DoWithdraw(std::istream& in, std::ostream& out, Account& acct, TransactionLog* log) { // withdraw function
        double amt = ReadMoney(in, out, " Withdraw amount. ", 0.01, 1000000.0); // read withdrawal amount
        if (acct.withdraw(amt)) { // attempt withdrawal
            out << " Dispensed. $" << amt << "\n New balance. $" << acct.getBalance() << "\n"; // show updated balance
            if (log) log->logWithdraw(acct.card(), amt, acct.getBalance(), nowStamp()); // log withdrawal
        }
        else { // insufficient funds
            out << " Withdraw blocked by insufficient funds\n"; // show message
        }
    } // end DoWithdraw

    void DoTransfer(std::istream& in, std::ostream& out, Account& from, Account& to, TransactionLog* log) { // transfer function
        out << " Transfer checking to savings\n"; // explain operation
        double amt = ReadMoney(in, out, " Amount. ", 0.01, 1000000.0); // read amount
        if (from.transferTo(to, amt)) { // attempt transfer
            out << " Transferred. $" << amt << "\n Checking. $" << from.getBalance() << "   Savings. $" << to.getBalance() << "\n"; // show balances
            if (log) log->logTransfer(from.card(), to.card(), amt, from.getBalance(), nowStamp()); // log transfer
        }
        else { // not enough money
            out << " Transfer blocked by insufficient funds\n"; // display failure message
        }
    } // end DoTransfer

}