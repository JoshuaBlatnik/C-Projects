// Ensures this header file is only included once during compilation.
#pragma once

// Includes the standard string library so std::string can be used.
#include <string>

// Includes the Character class definition so Character pointers can be used.
#include "Character.h"

// Declares a function that ensures two fighter names are not identical.
// The names are passed as pointers so they can be modified directly if needed.
void ValidateDistinctNames(std::string* aName, std::string* bName);

// Declares the main duel function that controls the combat loop.
// The two fighters are passed as pointers so their state can be modified in place.
// The difficulty is passed as a pointer so changes persist outside the function.
void Duel(Character* a, Character* b, int* difficulty);