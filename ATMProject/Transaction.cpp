#include "Transaction.h" // include header for transaction structures and class
#include <iostream> // include input and output stream library

namespace atmapp { // begin atmapp namespace

    static const char* typeName(TxType t) { // helper function to return transaction type as string
        switch (t) { // determine which transaction type
        case TxType::Deposit: return "Deposit"; // label for deposit
        case TxType::Withdraw: return "Withdraw"; // label for withdrawal
        case TxType::Transfer: return "Transfer"; // label for transfer
        } // end switch
        return "?"; // fallback if type unknown
    } // end typeName

    void TransactionLog::logDeposit(const std::string& card, double amount, double balanceAfter, const std::string& ts) { // record deposit transaction
        entries.push_back(Transaction{ TxType::Deposit, card, "", amount, balanceAfter, ts }); // add new deposit entry to list
    } // end logDeposit

    void TransactionLog::logWithdraw(const std::string& card, double amount, double balanceAfter, const std::string& ts) { // record withdrawal transaction
        entries.push_back(Transaction{ TxType::Withdraw, card, "", amount, balanceAfter, ts }); // add new withdrawal entry
    } // end logWithdraw

    void TransactionLog::logTransfer(const std::string& fromCard, const std::string& toCard, double amount, double fromBalanceAfter, const std::string& ts) { // record transfer transaction
        entries.push_back(Transaction{ TxType::Transfer, fromCard, toCard, amount, fromBalanceAfter, ts }); // add new transfer entry
    } // end logTransfer

    void TransactionLog::print(std::ostream& out) const { // print all recorded transactions
        if (entries.empty()) { // check if there are any records
            out << "No transactions recorded.\n"; // print message if none
            return; // exit function
        } // end if
        out << "\n=== Transaction History ===\n"; // print header
        for (const auto& tx : entries) { // loop through transaction entries
            out << " [" << tx.timestamp << "] "; // print timestamp
            switch (tx.type) { // handle based on transaction type
            case TxType::Deposit:  out << "Deposit $" << tx.amount << " on " << tx.fromCard; break; // print deposit details
            case TxType::Withdraw: out << "Withdraw $" << tx.amount << " on " << tx.fromCard; break; // print withdrawal details
            case TxType::Transfer: out << "Transfer $" << tx.amount << " from " << tx.fromCard << " to " << tx.toCard; break; // print transfer details
            } // end switch
            out << "  Balance after. $" << tx.balanceAfter << "\n"; // print balance after transaction
        } // end for
    } // end print

}