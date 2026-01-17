#pragma once // prevent multiple inclusion of this header file
#include <string> // include string type
#include <vector> // include vector container
#include <iosfwd> // forward declare iostream types for faster compilation

namespace atmapp { // begin atmapp namespace

    enum class TxType { Deposit, Withdraw, Transfer }; // define transaction types for clarity

    struct Transaction { // define structure to store transaction data
        TxType type; // type of transaction (deposit, withdraw, transfer)
        std::string fromCard; // originating card number
        std::string toCard; // destination card for transfers
        double amount; // transaction amount
        double balanceAfter; // account balance after transaction
        std::string timestamp; // time of transaction
    }; // end struct Transaction

    class TransactionLog { // define class to manage a list of transactions
    public: // public functions accessible to other files
        void logDeposit(const std::string& card, double amount, double balanceAfter, const std::string& ts); // record a deposit
        void logWithdraw(const std::string& card, double amount, double balanceAfter, const std::string& ts); // record a withdrawal
        void logTransfer(const std::string& fromCard, const std::string& toCard, double amount, double fromBalanceAfter, const std::string& ts); // record a transfer
        void print(std::ostream& out) const; // print transaction history
        bool empty() const { return entries.empty(); } // check if log is empty

    private: // internal data
        std::vector<Transaction> entries; // list of all recorded transactions
    }; // end class TransactionLog

}