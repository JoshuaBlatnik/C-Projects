#include "Finance.h" // include header for FinanceLog and FinEvent
#include <iostream> // include input and output stream library
#include <algorithm> // include standard algorithms
#include <numeric> // include numeric operations for sums

namespace atmapp { // begin atmapp namespace

    void FinanceLog::set(std::vector<FinEvent> events) { // set new list of financial events
        m_events = std::move(events); // move provided events into internal storage
    } // end set

    void FinanceLog::clear() { // remove all stored financial events
        m_events.clear(); // clear internal vector
    } // end clear

    const std::vector<FinEvent>& FinanceLog::all() const { // return read-only reference to all events
        return m_events; // return event list
    } // end all

    void FinanceLog::printPurchases(std::ostream& out, int limit) const { // display purchase transactions up to limit
        int shown = 0; // counter for printed entries
        out << "\nAssistant. Here are recent card purchases.\n"; // header message
        for (const auto& e : m_events) { // iterate through stored events
            if (e.kind != FinEvent::Kind::Purchase) continue; // skip non-purchase entries
            out << " " << e.date << "  $" << e.amount << "  " << e.store << "  " << e.location << "  " << e.item << "\n"; // print purchase details
            if (++shown >= limit) break; // stop if limit reached
        } // end for
        if (shown == 0) out << " No purchases found.\n"; // message when no purchases exist
    } // end printPurchases

    void FinanceLog::printPaychecks(std::ostream& out, int limit) const { // display paycheck transactions up to limit
        int shown = 0; // counter for printed entries
        out << "\nAssistant. Here are recent paychecks.\n"; // header message
        for (const auto& e : m_events) { // iterate through stored events
            if (e.kind != FinEvent::Kind::Paycheck) continue; // skip non-paycheck entries
            out << " " << e.date << "  $" << e.amount << "  " << e.store << "  " << e.location << "\n"; // print paycheck details
            if (++shown >= limit) break; // stop if limit reached
        } // end for
        if (shown == 0) out << " No paychecks found.\n"; // message when no paychecks exist
    } // end printPaychecks

    double FinanceLog::monthlyIncomeEstimate() const { // estimate average monthly income
        double sum = 0.0; // total income accumulator
        for (const auto& e : m_events) if (e.kind == FinEvent::Kind::Paycheck) sum += e.amount; // add up paycheck amounts
        return sum / 3.0; // divide by three months to estimate monthly income
    } // end monthlyIncomeEstimate

    double FinanceLog::monthlySpendEstimate() const { // estimate average monthly spending
        double sum = 0.0; // total spending accumulator
        for (const auto& e : m_events) if (e.kind == FinEvent::Kind::Purchase) sum += e.amount; // add up purchase amounts
        return sum / 3.0; // divide by three months to estimate monthly spending
    } // end monthlySpendEstimate

}