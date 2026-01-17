#include "ATM.h" // include ATM declarations
#include "Account.h" // include Account class
#include "Transaction.h" // include transaction log types
#include "Finance.h" // include finance log types
#include "Credit.h" // include credit profile
#include "DataGen.h" // include random data generator

#include <iostream> // include stream io
#include <vector> // include vector container
#include <limits> // include numeric limits

using namespace atmapp; // use the atmapp namespace for brevity

struct Customer { // define a simple customer record
    Account checking; // checking account object
    Account savings; // savings account object
}; // end of Customer

static int readIntBounded(std::istream& in, std::ostream& out, int lo, int hi) { // read a bounded integer
    int v{}; // hold the input value
    while (true) { // loop until a valid value is entered
        if (in >> v && v >= lo && v <= hi) return v; // accept value inside bounds and return it
        out << " Enter a number between " << lo << " and " << hi << ". "; // prompt for a valid number
        in.clear(); // clear error flags
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the rest of the line
    } // end while
} // end readIntBounded

int main() { // program entry point
    std::vector<Customer> customers; // list of customers
    customers.push_back(Customer{ Account("Josh",  "Card. **** **** **** 4242", 1234, 1250.00), // add Josh checking
                                  Account("Josh",  "Savings. **** **** **** 8844", 1234, 3000.00) }); // add Josh savings
    customers.push_back(Customer{ Account("Ava",   "Card. **** **** **** 1111", 1111, 800.00), // add Ava checking
                                  Account("Ava",   "Savings. **** **** **** 9111", 1111, 1200.00) }); // add Ava savings
    customers.push_back(Customer{ Account("Liam",  "Card. **** **** **** 2222", 2222, 920.00), // add Liam checking
                                  Account("Liam",  "Savings. **** **** **** 9222", 2222, 400.00) }); // add Liam savings
    customers.push_back(Customer{ Account("Mia",   "Card. **** **** **** 3333", 3333, 450.50), // add Mia checking
                                  Account("Mia",   "Savings. **** **** **** 9333", 3333, 610.00) }); // add Mia savings
    customers.push_back(Customer{ Account("Noah",  "Card. **** **** **** 4444", 4444, 77.77), // add Noah checking
                                  Account("Noah",  "Savings. **** **** **** 9444", 4444, 88.88) }); // add Noah savings
    customers.push_back(Customer{ Account("Emma",  "Card. **** **** **** 5555", 5555, 5100.12), // add Emma checking
                                  Account("Emma",  "Savings. **** **** **** 9555", 5555, 2500.00) }); // add Emma savings
    customers.push_back(Customer{ Account("Lucas", "Card. **** **** **** 6666", 6666, 25.00), // add Lucas checking
                                  Account("Lucas", "Savings. **** **** **** 9666", 6666, 75.00) }); // add Lucas savings
    customers.push_back(Customer{ Account("Sophia","Card. **** **** **** 7777", 7777, 190.00), // add Sophia checking
                                  Account("Sophia","Savings. **** **** **** 9777", 7777, 310.00) }); // add Sophia savings
    customers.push_back(Customer{ Account("Elena", "Card. **** **** **** 8888", 8888, 999.99), // add Elena checking
                                  Account("Elena", "Savings. **** **** **** 9888", 8888, 150.00) }); // add Elena savings

    TransactionLog log; // create a transaction log
    FinanceLog fin; // create a finance log
    CreditProfile credit; // create a credit profile
    DataGen gen; // create a data generator

    auto seedEvents = gen.generateQuarterHistory(18, 2); // build sample events for three months
    fin.set(std::move(seedEvents)); // load events into the finance log

    ShowBanner(std::cout); // show the banner
    std::cout << "\nSelect a customer to insert their card.\n"; // prompt to choose a customer
    for (size_t i = 0; i < customers.size(); ++i) { // iterate over customers
        std::cout << " " << (i + 1) << ". " << customers[i].checking.owner() << "  [" << customers[i].checking.card() << "]\n"; // print a menu row
    } // end for
    std::cout << " Choice. "; // prompt for selection
    int idx = readIntBounded(std::cin, std::cout, 1, static_cast<int>(customers.size())) - 1; // read a valid index and convert to zero based

    if (!SignIn(std::cin, std::cout, customers[idx].checking)) { // verify pin for the chosen customer
        return 0; // end the program when sign in fails
    } // end if

    RunSession(std::cin, std::cout, customers[idx].checking, customers[idx].savings, &log, &fin, &credit); // start the interactive session
    return 0; // signal success
}