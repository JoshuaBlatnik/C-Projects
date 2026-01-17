#pragma once // ensure this header is only included once per build
#include <iosfwd> // forward declare iostream types for efficiency

namespace atmapp { // begin atmapp namespace

    class CreditProfile { // define CreditProfile class to handle credit scoring
    public: // public methods accessible from outside
        CreditProfile(); // constructor to initialize credit score
        void compute(double checkingBal, double savingsBal, double monthlyIncome, double monthlySpend); // calculate credit score using financial inputs
        int score() const; // return the current stored score
        void print(std::ostream& out) const; // print formatted credit score with message

    private: // internal data hidden from external access
        int m_score; // integer variable holding the credit score value
    }; // end of CreditProfile class

}