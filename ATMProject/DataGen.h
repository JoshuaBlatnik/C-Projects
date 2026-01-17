#pragma once // prevent multiple inclusion of this header file
#include <vector> // include vector for dynamic arrays
#include <string> // include string class
#include <random> // include random number generation utilities
#include <chrono> // include time utilities for seeding
#include "Finance.h" // include finance definitions for FinEvent

namespace atmapp { // begin atmapp namespace

    class DataGen { // define the DataGen class
    public: // public interface
        explicit DataGen(uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count()); // constructor with optional seed defaulting to current time
        std::vector<FinEvent> generateQuarterHistory(int purchasesPerMonth, int paychecksPerMonth); // create three months of random purchase and paycheck history

    private: // private members
        std::mt19937_64 rng; // 64-bit random number generator
        std::string randomDateInPastMonths(int monthsBack); // helper function to make a random date string
        FinEvent randomPurchase(); // helper to generate random purchase event
        FinEvent randomPaycheck(); // helper to generate random paycheck event
    }; // end of class

}