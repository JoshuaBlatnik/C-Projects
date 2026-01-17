// Ensures this header file is only included once during compilation.
#pragma once

// Includes the string library so the program can use std::string.
#include <string>

// Declares the Character class, which acts as the base class for all fighters.
class Character
{
public:
    // Stores the display name of the fighter.
    std::string Name;

    // Declares the default constructor that initializes stats.
    Character();

    // Declares a virtual destructor so derived classes clean up correctly.
    virtual ~Character();

    // Declares a function that prints dialogue using the fighter own name.
    void Talk(const std::string& stuffToSay) const;

    // Declares an overloaded function that prints dialogue using a custom name.
    void Talk(std::string name, std::string stuffToSay) const;

    // Declares a function that returns the current health value.
    int GetHealth() const;

    // Declares a function that returns the maximum health value.
    int GetMaxHealth() const;

    // Declares a function that sets current health while enforcing limits.
    void SetHealth(int value);

    // Declares a function that resets health, mana, and cooldown to starting values.
    void ResetHealth();

    // Declares a function that returns the current mana value.
    int GetMana() const;

    // Declares a function that returns the maximum mana value.
    int GetMaxMana() const;

    // Declares a function that subtracts mana when abilities are used.
    void SpendMana(int amount);

    // Declares a function that returns the remaining cooldown turns.
    int GetCooldown() const;

    // Declares a function that advances cooldown and handles turn based updates.
    void TickCooldown();

    // Declares a function that returns true when the special ability is ready.
    bool CanUseSpecial() const;

    // Declares a function that starts the cooldown after a special ability is used.
    void TriggerCooldown();

    // Declares a virtual function that prints a fighter introduction line.
    virtual void Speak() const;

    // Declares a virtual function that returns the basic attack value.
    virtual int Attack() const;

    // Declares a virtual function that returns the fighter class name for UI display.
    virtual const char* ClassName() const;

    // Declares a virtual function that returns the special ability name.
    virtual const char* SpecialName() const;

    // Declares a virtual function that returns the base special ability damage.
    virtual int SpecialDamage() const;

    // Declares a virtual function that returns the cooldown duration for the special ability.
    virtual int SpecialCooldownTurns() const;

    // Declares a virtual function that returns the mana cost for the special ability.
    virtual int SpecialManaCost() const;

    // Declares a virtual function that prints the special ability animation text.
    virtual void SpecialAnimation() const;

protected:
    // Declares a helper that allows derived classes to set maximum health safely.
    void SetMaxHealth(int value);

    // Declares a helper that allows derived classes to set maximum mana safely.
    void SetMaxMana(int value);

private:
    // Stores the current health value and keeps it private for encapsulation.
    int Health;

    // Stores the maximum health value and keeps it private for encapsulation.
    int MaxHealth;

    // Stores the current mana value and keeps it private for encapsulation.
    int Mana;

    // Stores the maximum mana value and keeps it private for encapsulation.
    int MaxMana;

    // Stores the remaining cooldown turns and keeps it private for encapsulation.
    int Cooldown;
};

// Declares the Ninja class as a derived fighter type.
class Ninja : public Character
{
public:
    // Declares the constructor that initializes a Ninja with a name.
    explicit Ninja(const std::string& name);

    // Declares the ninja basic animation function.
    void ThrowStars() const;

    // Overrides the introduction line for a Ninja.
    void Speak() const override;

    // Overrides the basic attack value for a Ninja.
    int Attack() const override;

    // Overrides the class name string for UI display.
    const char* ClassName() const override;

    // Overrides the special ability name.
    const char* SpecialName() const override;

    // Overrides the special ability damage.
    int SpecialDamage() const override;

    // Overrides the special ability cooldown duration.
    int SpecialCooldownTurns() const override;

    // Overrides the special ability mana cost.
    int SpecialManaCost() const override;

    // Overrides the special ability animation behavior.
    void SpecialAnimation() const override;
};

// Declares the Pirate class as a derived fighter type.
class Pirate : public Character
{
public:
    // Declares the constructor that initializes a Pirate with a name.
    explicit Pirate(const std::string& name);

    // Declares the pirate basic animation function.
    void UseSword() const;

    // Overrides the introduction line for a Pirate.
    void Speak() const override;

    // Overrides the basic attack value for a Pirate.
    int Attack() const override;

    // Overrides the class name string for UI display.
    const char* ClassName() const override;

    // Overrides the special ability name.
    const char* SpecialName() const override;

    // Overrides the special ability damage.
    int SpecialDamage() const override;

    // Overrides the special ability cooldown duration.
    int SpecialCooldownTurns() const override;

    // Overrides the special ability mana cost.
    int SpecialManaCost() const override;

    // Overrides the special ability animation behavior.
    void SpecialAnimation() const override;
};

// Declares the Samurai class as a derived fighter type.
class Samurai : public Character
{
public:
    // Declares the constructor that initializes a Samurai with a name.
    explicit Samurai(const std::string& name);

    // Overrides the introduction line for a Samurai.
    void Speak() const override;

    // Overrides the basic attack value for a Samurai.
    int Attack() const override;

    // Overrides the class name string for UI display.
    const char* ClassName() const override;

    // Overrides the special ability name.
    const char* SpecialName() const override;

    // Overrides the special ability damage.
    int SpecialDamage() const override;

    // Overrides the special ability cooldown duration.
    int SpecialCooldownTurns() const override;

    // Overrides the special ability mana cost.
    int SpecialManaCost() const override;

    // Overrides the special ability animation behavior.
    void SpecialAnimation() const override;
};

// Declares the Viking class as a derived fighter type.
class Viking : public Character
{
public:
    // Declares the constructor that initializes a Viking with a name.
    explicit Viking(const std::string& name);

    // Overrides the introduction line for a Viking.
    void Speak() const override;

    // Overrides the basic attack value for a Viking.
    int Attack() const override;

    // Overrides the class name string for UI display.
    const char* ClassName() const override;

    // Overrides the special ability name.
    const char* SpecialName() const override;

    // Overrides the special ability damage.
    int SpecialDamage() const override;

    // Overrides the special ability cooldown duration.
    int SpecialCooldownTurns() const override;

    // Overrides the special ability mana cost.
    int SpecialManaCost() const override;

    // Overrides the special ability animation behavior.
    void SpecialAnimation() const override;
};

// Declares a factory style function that returns the correct fighter pointer for a class choice.
Character* CreateFighter(int choice, const std::string& name, Ninja* n, Pirate* p, Samurai* s, Viking* v);