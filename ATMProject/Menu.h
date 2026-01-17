#pragma once // ensure this header file is only included once during compilation
#include <iosfwd> // forward declaration of iostream types for faster compilation

namespace atmapp { // begin atmapp namespace

	void ShowMenu(std::ostream& out); // function to display the ATM menu options
	int ReadMenuChoice(std::istream& in, std::ostream& out); // function to read and validate user menu selection

}