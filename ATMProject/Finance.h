#pragma once // prevent multiple inclusion of this header file
#include <string> // include string type
#include <vector> // include vector container
#include <iosfwd> // forward declare iostream types for efficiency

namespace atmapp { // begin atmapp namespace

    struct FinEvent { // define FinEvent struct for storing financial records
        enum class Kind { Purchase, Paycheck }; // define event types: purchase or paycheck
        Kind kind; // specify whether the event is a purchase or paycheck
        std::string date; // date of the event
        std::string store; // store or employer name
        std::string location; // location of store or source
        std::string item; // item name or description
        double amount; // transaction amount
    }; // end of FinEvent struct

    class FinanceLog { // define FinanceLog class to hold and manage FinEvent records
    public: // public functions
        void set(std::vector<FinEvent> events); // replace internal list with given events
        void clear(); // remove all stored events
        const std::vector<FinEvent>& all() const; // access full list of events
        void printPurchases(std::ostream& out, int limit = 25) const; // print recent purchases up to limit
        void printPaychecks(std::ostream& out, int limit = 25) const; // print recent paychecks up to limit
        double monthlyIncomeEstimate() const; // estimate monthly income from paycheck data
        double monthlySpendEstimate() const; // estimate monthly spending from purchase data

    private: // private data members
        std::vector<FinEvent> m_events; // container for all financial events
    }; // end of FinanceLog class

}