#include "Account.h" // include header for Account class definition
#include <utility> // include utility for std::move

namespace atmapp { // begin atmapp namespace

    Account::Account(std::string owner, std::string card, int pin, double balance) // constructor with initialization
        : m_owner(std::move(owner)), m_card(std::move(card)), m_pin(pin), m_balance(balance) { // move owner and card to members, set pin and balance
    } // end constructor

    const std::string& Account::owner() const { return m_owner; } // return reference to account owner's name
    const std::string& Account::card() const { return m_card; } // return reference to card identifier
    bool Account::checkPin(int entered) const { return entered == m_pin; } // verify if entered pin matches stored pin
    double Account::getBalance() const { return m_balance; } // return current balance value

    bool Account::deposit(double amount) { // deposit funds into account
        if (amount <= 0) return false; // block invalid or negative deposits
        m_balance += amount; // add amount to balance
        return true; // indicate success
    } // end deposit

    bool Account::withdraw(double amount) { // withdraw funds from account
        if (amount <= 0 || amount > m_balance) return false; // prevent overdraft or invalid withdrawal
        m_balance -= amount; // subtract amount from balance
        return true; // indicate success
    } // end withdraw

    bool Account::transferTo(Account& other, double amount) { // transfer money to another account
        if (amount <= 0 || amount > m_balance) return false; // ensure sufficient funds and valid input
        m_balance -= amount; // deduct from sender
        other.m_balance += amount; // add to receiver
        return true; // indicate success
    } // end transferTo

}