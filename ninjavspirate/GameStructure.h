// Ensures this header file is only included once during compilation.
#pragma once

// Declares the GameStructure class, which acts as an abstract base class for all game elements.
class GameStructure {
public:
    // Declares a virtual destructor so derived classes clean up properly when deleted through a base pointer.
    virtual ~GameStructure() = default;

    // Declares a pure virtual Help method that all derived classes must implement.
    virtual void Help() = 0;
};