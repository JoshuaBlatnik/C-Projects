#pragma once // ensure this header is only included once during compilation
#include "Account.h" // include Account class definition
#include <iosfwd> // forward declare input/output stream types for efficiency

namespace atmapp { // begin atmapp namespace

	class TransactionLog; // forward declaration of TransactionLog class
	class FinanceLog; // forward declaration of FinanceLog class
	class CreditProfile; // forward declaration of CreditProfile class

	void ShowBanner(std::ostream& out); // display welcome banner
	bool SignIn(std::istream& in, std::ostream& out, const Account& probe); // handle sign-in authentication process
	void RunSession(std::istream& in, std::ostream& out, Account& active, Account& savings, TransactionLog* log = nullptr, FinanceLog* fin = nullptr, CreditProfile* credit = nullptr); // control the main ATM session logic
	void DoBalance(std::ostream& out, const Account& checking, const Account& savings); // show balances for checking and savings accounts
	void DoDeposit(std::istream& in, std::ostream& out, Account& acct, TransactionLog* log = nullptr); // process a deposit operation
	void DoWithdraw(std::istream& in, std::ostream& out, Account& acct, TransactionLog* log = nullptr); // process a withdrawal operation
	void DoTransfer(std::istream& in, std::ostream& out, Account& from, Account& to, TransactionLog* log = nullptr); // transfer funds between accounts
	int ReadInt(std::istream& in, std::ostream& out, const char* prompt, int minVal, int maxVal); // read integer input safely within range
	double ReadMoney(std::istream& in, std::ostream& out, const char* prompt, double minVal, double maxVal); // read money input safely within range

}