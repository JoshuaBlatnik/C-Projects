#include "Credit.h" // include header for CreditProfile class
#include <iostream> // include input and output stream library
#include <algorithm> // include algorithms like min and max

namespace atmapp { // begin atmapp namespace

    CreditProfile::CreditProfile() : m_score(680) {} // constructor sets starting credit score to 680

    void CreditProfile::compute(double checkingBal, double savingsBal, double monthlyIncome, double monthlySpend) { // compute updated credit score
        double creditLimit = 5000.0; // assume a fixed credit limit
        double util = std::min(1.0, std::max(0.0, monthlySpend / creditLimit)); // calculate credit utilization, clamped between 0 and 1
        double savingsFactor = std::min(1.0, savingsBal / 10000.0); // scale savings up to a max effect at 10,000
        double incomeSafety = monthlyIncome > 0.0 ? std::min(1.0, (monthlyIncome - monthlySpend) / std::max(1.0, monthlyIncome)) : 0.0; // measure how much of income remains after spending
        double base = 640.0; // baseline score
        double utilImpact = (1.0 - util) * 150.0; // reward for lower utilization
        double savingsImpact = savingsFactor * 40.0; // reward for higher savings
        double bufferImpact = incomeSafety * 20.0; // reward for leftover income
        double checkImpact = std::min(40.0, checkingBal / 2500.0 * 40.0); // small boost from checking balance up to a cap
        int s = static_cast<int>(base + utilImpact + savingsImpact + bufferImpact + checkImpact); // total computed score
        m_score = std::max(300, std::min(850, s)); // clamp final score between 300 and 850
    } // end compute

    int CreditProfile::score() const { // return the stored credit score
        return m_score;
    } // end score

    void CreditProfile::print(std::ostream& out) const { // display the current score with interpretation
        out << "\nAssistant. Your current credit score estimate. " << m_score << "\n"; // print score
        if (m_score >= 740) out << " Strong profile.\n"; // message for high score
        else if (m_score >= 670) out << " Good standing.\n"; // message for average score
        else out << " Needs work.\n"; // message for low score
    } // end print

}