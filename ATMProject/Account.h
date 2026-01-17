#pragma once // prevent multiple inclusion of this header file
#include <string> // include string type for storing text data

namespace atmapp { // begin atmapp namespace

    class Account { // define Account class to represent a bank account
    public: // public interface accessible to other parts of the program
        Account(std::string owner, std::string card, int pin, double balance); // constructor initializing owner, card, pin, and balance
        const std::string& owner() const; // return reference to account owner's name
        const std::string& card() const; // return reference to card identifier string
        bool checkPin(int entered) const; // verify entered pin against stored pin
        double getBalance() const; // return current balance of the account
        bool deposit(double amount); // deposit funds into the account
        bool withdraw(double amount); // withdraw funds from the account
        bool transferTo(Account& other, double amount); // transfer funds to another account

    private: // internal data members not accessible outside the class
        std::string m_owner; // name of account owner
        std::string m_card; // masked card identifier
        int m_pin; // personal identification number
        double m_balance; // current account balance
    }; // end of Account class

}