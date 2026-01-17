#include "DataGen.h" // include header for DataGen class
#include <array> // include fixed size array container
#include <sstream> // include string stream utilities
#include <iomanip> // include formatting for output
#include <ctime> // include time handling functions
#include <algorithm> // include algorithms like sort

namespace atmapp { // begin atmapp namespace

    static const std::array<const char*, 18> kItems = { // define array of item names
        "Coffee beans","Grocery basket","Phone charger","Motor oil","Tire inflator","Running shoes",
        "Hoodie","USB drive","Notebook","LED bulbs","Sunscreen","Protein bars",
        "Video game","Keyboard","Mouse pad","Windshield wipers","Dog food","Bottled water"
    };

    static const std::array<const char*, 14> kStores = { // define array of store names
        "Target","Best Buy","Costco","Walmart","AutoZone","Whole Foods","GameStop",
        "Menards","Home Depot","Trader Joes","Kohls","REI","Dollar General","Local Market"
    };

    static const std::array<const char*, 14> kCities = { // define array of city and state combinations
        "Phoenix AZ","Tempe AZ","Scottsdale AZ","Flagstaff AZ","Tucson AZ","Las Vegas NV",
        "San Diego CA","Los Angeles CA","Denver CO","Austin TX","Dallas TX","Omaha NE","Chicago IL","Madison WI"
    };

    static const std::array<const char*, 8> kEmployers = { // define array of employer names
        "Unified Tech","Desert Labs","North Valley Metals","Sunrise Retail",
        "Canyon Logistics","Prairie Systems","River City Bank","Blue Ridge Media"
    };

    DataGen::DataGen(uint64_t seed) : rng(seed) {} // constructor initializes random generator with seed

    std::string DataGen::randomDateInPastMonths(int monthsBack) { // create random date string in previous months
        std::uniform_int_distribution<int> dday(0, 27); // random day generator
        std::time_t t = std::time(nullptr); // current time in seconds
        std::tm tm{}; // create a tm structure
#if defined(_WIN32)
        localtime_s(&tm, &t); // convert time to local on Windows
#else
        localtime_r(&t, &tm); // convert time to local on other systems
#endif
        int month = tm.tm_mon + 1; // extract current month
        int year = tm.tm_year + 1900; // extract current year
        month -= monthsBack; // subtract months to go back in time
        while (month <= 0) { month += 12; --year; } // adjust year if month goes below January
        int day = 1 + dday(rng); // pick a random day in the month
        std::ostringstream os; // string builder for formatted date
        os << std::setfill('0') << std::setw(4) << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day; // format YYYY-MM-DD
        return os.str(); // return formatted date
    }

    FinEvent DataGen::randomPurchase() { // generate random purchase event
        std::uniform_int_distribution<int> di(0, static_cast<int>(kItems.size() - 1)); // random item index
        std::uniform_int_distribution<int> ds(0, static_cast<int>(kStores.size() - 1)); // random store index
        std::uniform_int_distribution<int> dc(0, static_cast<int>(kCities.size() - 1)); // random city index
        std::uniform_real_distribution<double> damt(6.0, 420.0); // random purchase amount
        FinEvent e; // create event object
        e.kind = FinEvent::Kind::Purchase; // mark as purchase
        e.date = randomDateInPastMonths(std::uniform_int_distribution<int>(0, 2)(rng)); // assign a random recent date
        e.store = kStores[ds(rng)]; // assign a random store
        e.location = kCities[dc(rng)]; // assign a random city
        e.item = kItems[di(rng)]; // assign a random item
        e.amount = std::round(damt(rng) * 100.0) / 100.0; // round price to two decimals
        return e; // return purchase event
    }

    FinEvent DataGen::randomPaycheck() { // generate random paycheck event
        std::uniform_int_distribution<int> de(0, static_cast<int>(kEmployers.size() - 1)); // random employer index
        std::uniform_real_distribution<double> damt(950.0, 2450.0); // random paycheck amount
        FinEvent e; // create event
        e.kind = FinEvent::Kind::Paycheck; // mark as paycheck
        e.date = randomDateInPastMonths(std::uniform_int_distribution<int>(0, 2)(rng)); // assign random recent date
        e.store = kEmployers[de(rng)]; // assign employer name
        e.location = "Payroll"; // location labeled as payroll
        e.item = "Direct deposit"; // describe transaction type
        e.amount = std::round(damt(rng) * 100.0) / 100.0; // round amount to two decimals
        return e; // return paycheck event
    }

    std::vector<FinEvent> DataGen::generateQuarterHistory(int purchasesPerMonth, int paychecksPerMonth) { // build three months of events
        std::vector<FinEvent> out; // vector to store events
        out.reserve(purchasesPerMonth * 3 + paychecksPerMonth * 3); // preallocate memory for performance
        for (int m = 0; m < 3; ++m) { // loop for each month
            for (int i = 0; i < purchasesPerMonth; ++i) { // generate purchase events
                FinEvent e = randomPurchase(); // create purchase
                e.date = randomDateInPastMonths(m); // assign date for current month offset
                out.push_back(std::move(e)); // add purchase to vector
            }
            for (int j = 0; j < paychecksPerMonth; ++j) { // generate paycheck events
                FinEvent p = randomPaycheck(); // create paycheck
                p.date = randomDateInPastMonths(m); // assign date for current month offset
                out.push_back(std::move(p)); // add paycheck to vector
            }
        }
        std::stable_sort(out.begin(), out.end(), [](const FinEvent& a, const FinEvent& b) { return a.date > b.date; }); // sort events by descending date
        return out; // return completed history
    }

}