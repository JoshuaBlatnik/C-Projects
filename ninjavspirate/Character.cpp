// Includes the Character class definitions so this file can implement them.
#include "Character.h"

// Includes utility functions such as TypeOut and SetColor.
#include "Utilities.h"

// Allows use of standard library names without prefixing them with std::.
using namespace std;

// Defines the default constructor for the Character base class.
Character::Character()
{
    // Assigns a default name to the character.
    Name = "Fighter";

    // Sets the maximum health value.
    MaxHealth = 100;

    // Initializes current health to the maximum value.
    Health = 100;

    // Sets the maximum mana value.
    MaxMana = 100;

    // Initializes current mana to the maximum value.
    Mana = 100;

    // Initializes the special ability cooldown to zero.
    Cooldown = 0;
}

// Defines the virtual destructor for the Character class.
Character::~Character()
{
    // Outputs a message indicating the character has exited the arena.
    TypeOut(Name + " leaves the arena.\n");
}

// Outputs dialogue using the character’s own name.
void Character::Talk(const string& stuffToSay) const
{
    // Prints the character name followed by the provided message.
    TypeOut(Name + ": " + stuffToSay + "\n");
}

// Outputs dialogue using a custom speaker name.
void Character::Talk(string name, string stuffToSay) const
{
    // Prints the provided name followed by the provided message.
    TypeOut(name + ": " + stuffToSay + "\n");
}

// Returns the current health value.
int Character::GetHealth() const
{
    // Returns the stored health.
    return Health;
}

// Returns the maximum health value.
int Character::GetMaxHealth() const
{
    // Returns the maximum health.
    return MaxHealth;
}

// Sets the maximum health value while enforcing valid limits.
void Character::SetMaxHealth(int value)
{
    // Ensures the maximum health is at least one.
    if (value < 1) value = 1;

    // Updates the maximum health value.
    MaxHealth = value;

    // Clamps current health if it exceeds the new maximum.
    if (Health > MaxHealth) Health = MaxHealth;
}

// Sets the current health value while enforcing valid bounds.
void Character::SetHealth(int value)
{
    // Prevents health from going below zero.
    if (value < 0) value = 0;

    // Prevents health from exceeding the maximum.
    if (value > MaxHealth) value = MaxHealth;

    // Updates the health value.
    Health = value;
}

// Sets the maximum mana value while enforcing valid limits.
void Character::SetMaxMana(int value)
{
    // Ensures the maximum mana is at least one.
    if (value < 1) value = 1;

    // Updates the maximum mana value.
    MaxMana = value;

    // Clamps current mana if it exceeds the new maximum.
    if (Mana > MaxMana) Mana = MaxMana;
}

// Returns the current mana value.
int Character::GetMana() const
{
    // Returns the stored mana.
    return Mana;
}

// Returns the maximum mana value.
int Character::GetMaxMana() const
{
    // Returns the maximum mana.
    return MaxMana;
}

// Deducts mana when abilities are used.
void Character::SpendMana(int amount)
{
    // Prevents negative mana deductions.
    if (amount < 0) amount = 0;

    // Subtracts the mana cost.
    Mana -= amount;

    // Ensures mana does not drop below zero.
    if (Mana < 0) Mana = 0;
}

// Resets health, mana, and cooldown values.
void Character::ResetHealth()
{
    // Restores health to the maximum value.
    Health = MaxHealth;

    // Restores mana to the maximum value.
    Mana = MaxMana;

    // Clears any active cooldown.
    Cooldown = 0;
}

// Returns the remaining cooldown turns.
int Character::GetCooldown() const
{
    // Returns the cooldown value.
    return Cooldown;
}

// Advances cooldowns and regenerates mana each turn.
void Character::TickCooldown()
{
    // Decreases the cooldown if it is active.
    if (Cooldown > 0) Cooldown -= 1;

    // Regenerates mana if it is not already full.
    if (Mana < MaxMana)
    {
        // Adds a fixed amount of mana regeneration.
        Mana += 10;

        // Prevents mana from exceeding the maximum.
        if (Mana > MaxMana) Mana = MaxMana;
    }
}

// Determines whether the special ability can be used.
bool Character::CanUseSpecial() const
{
    // Returns true if no cooldown is active.
    return Cooldown == 0;
}

// Activates the cooldown after using a special ability.
void Character::TriggerCooldown()
{
    // Sets the cooldown based on the character’s special ability.
    Cooldown = SpecialCooldownTurns();

    // Prevents negative cooldown values.
    if (Cooldown < 0) Cooldown = 0;
}

// Outputs default dialogue for a character.
void Character::Speak() const
{
    // Prints a generic ready message.
    TypeOut(Name + ": Ready.\n");
}

// Returns the base attack value.
int Character::Attack() const
{
    // Returns a default attack strength.
    return 10;
}

// Returns the class name of the character.
const char* Character::ClassName() const
{
    // Returns the base class name.
    return "Character";
}

// Returns the name of the special ability.
const char* Character::SpecialName() const
{
    // Returns a default special ability name.
    return "Special";
}

// Returns the base special damage value.
int Character::SpecialDamage() const
{
    // Returns a default special damage amount.
    return 15;
}

// Returns the cooldown duration for the special ability.
int Character::SpecialCooldownTurns() const
{
    // Returns the default cooldown length.
    return 3;
}

// Returns the mana cost required to use the special ability.
int Character::SpecialManaCost() const
{
    // Returns the default mana cost.
    return 40;
}

// Performs the default special ability animation.
void Character::SpecialAnimation() const
{
    // Outputs a generic special move message.
    TypeOut(Name + " uses a special move.\n");
}

// Constructs a Ninja character with custom stats.
Ninja::Ninja(const string& name)
{
    // Sets the ninja name.
    Name = name;

    // Sets the ninja maximum health.
    SetMaxHealth(95);

    // Sets the ninja maximum mana.
    SetMaxMana(100);

    // Resets health, mana, and cooldown values.
    ResetHealth();
}

// Performs the ninja throwing stars animation.
void Ninja::ThrowStars() const
{
#ifdef _WIN32
    // Sets the console text color to cyan on Windows.
    SetColor(11);
#endif
    // Outputs the throwing stars animation text.
    TypeOut(Name + ": Throwing stars.\n");
#ifdef _WIN32
    // Restores the default console color on Windows.
    SetColor(7);
#endif
}

// Outputs ninja-specific dialogue.
void Ninja::Speak() const
{
    // Prints a ninja-themed message.
    TypeOut(Name + ": The shadows follow me.\n");
}

// Returns the ninja base attack value.
int Ninja::Attack() const
{
    // Returns a stronger attack value than the base class.
    return 24;
}

// Returns the ninja class name.
const char* Ninja::ClassName() const
{
    // Returns the class identifier.
    return "Ninja";
}

// Returns the ninja special ability name.
const char* Ninja::SpecialName() const
{
    // Returns the ninja special name.
    return "Shadow Strike";
}

// Returns the ninja special damage value.
int Ninja::SpecialDamage() const
{
    // Returns the ninja special damage.
    return 34;
}

// Returns the ninja special cooldown duration.
int Ninja::SpecialCooldownTurns() const
{
    // Returns the ninja cooldown length.
    return 3;
}

// Returns the ninja special mana cost.
int Ninja::SpecialManaCost() const
{
    // Returns the ninja mana cost.
    return 45;
}

// Performs the ninja special animation.
void Ninja::SpecialAnimation() const
{
    // Executes the throwing stars animation.
    ThrowStars();

    // Outputs the special attack message.
    TypeOut(Name + ": Shadow Strike.\n");
}

// Constructs a Pirate character with custom stats.
Pirate::Pirate(const string& name)
{
    // Sets the pirate name.
    Name = name;

    // Sets the pirate maximum health.
    SetMaxHealth(105);

    // Sets the pirate maximum mana.
    SetMaxMana(100);

    // Resets health, mana, and cooldown values.
    ResetHealth();
}

// Performs the pirate sword attack animation.
void Pirate::UseSword() const
{
#ifdef _WIN32
    // Sets the console text color to red on Windows.
    SetColor(12);
#endif
    // Outputs the sword swing animation text.
    TypeOut(Name + ": Sword swing.\n");
#ifdef _WIN32
    // Restores the default console color on Windows.
    SetColor(7);
#endif
}

// Outputs pirate-specific dialogue.
void Pirate::Speak() const
{
    // Prints a pirate-themed message.
    TypeOut(Name + ": The sea calls my name.\n");
}

// Returns the pirate base attack value.
int Pirate::Attack() const
{
    // Returns the pirate attack strength.
    return 24;
}

// Returns the pirate class name.
const char* Pirate::ClassName() const
{
    // Returns the class identifier.
    return "Pirate";
}

// Returns the pirate special ability name.
const char* Pirate::SpecialName() const
{
    // Returns the pirate special name.
    return "Cannon Shot";
}

// Returns the pirate special damage value.
int Pirate::SpecialDamage() const
{
    // Returns the pirate special damage.
    return 36;
}

// Returns the pirate special cooldown duration.
int Pirate::SpecialCooldownTurns() const
{
    // Returns the pirate cooldown length.
    return 4;
}

// Returns the pirate special mana cost.
int Pirate::SpecialManaCost() const
{
    // Returns the pirate mana cost.
    return 55;
}

// Performs the pirate special animation.
void Pirate::SpecialAnimation() const
{
    // Executes the sword attack animation.
    UseSword();

    // Outputs the special attack message.
    TypeOut(Name + ": Cannon Shot.\n");
}

// Constructs a Samurai character with custom stats.
Samurai::Samurai(const string& name)
{
    // Sets the samurai name.
    Name = name;

    // Sets the samurai maximum health.
    SetMaxHealth(100);

    // Sets the samurai maximum mana.
    SetMaxMana(100);

    // Resets health, mana, and cooldown values.
    ResetHealth();
}

// Outputs samurai-specific dialogue.
void Samurai::Speak() const
{
    // Prints a samurai-themed message.
    TypeOut(Name + ": Honor decides this duel.\n");
}

// Returns the samurai base attack value.
int Samurai::Attack() const
{
    // Returns the samurai attack strength.
    return 22;
}

// Returns the samurai class name.
const char* Samurai::ClassName() const
{
    // Returns the class identifier.
    return "Samurai";
}

// Returns the samurai special ability name.
const char* Samurai::SpecialName() const
{
    // Returns the samurai special name.
    return "Iaido Cut";
}

// Returns the samurai special damage value.
int Samurai::SpecialDamage() const
{
    // Returns the samurai special damage.
    return 30;
}

// Returns the samurai special cooldown duration.
int Samurai::SpecialCooldownTurns() const
{
    // Returns the samurai cooldown length.
    return 2;
}

// Returns the samurai special mana cost.
int Samurai::SpecialManaCost() const
{
    // Returns the samurai mana cost.
    return 35;
}

// Performs the samurai special animation.
void Samurai::SpecialAnimation() const
{
    // Outputs the special attack message.
    TypeOut(Name + ": Iaido Cut.\n");
}

// Constructs a Viking character with custom stats.
Viking::Viking(const string& name)
{
    // Sets the viking name.
    Name = name;

    // Sets the viking maximum health.
    SetMaxHealth(120);

    // Sets the viking maximum mana.
    SetMaxMana(100);

    // Resets health, mana, and cooldown values.
    ResetHealth();
}

// Outputs viking-specific dialogue.
void Viking::Speak() const
{
    // Prints a viking-themed message.
    TypeOut(Name + ": The storm is here.\n");
}

// Returns the viking base attack value.
int Viking::Attack() const
{
    // Returns the viking attack strength.
    return 26;
}

// Returns the viking class name.
const char* Viking::ClassName() const
{
    // Returns the class identifier.
    return "Viking";
}

// Returns the viking special ability name.
const char* Viking::SpecialName() const
{
    // Returns the viking special name.
    return "Rage Smash";
}

// Returns the viking special damage value.
int Viking::SpecialDamage() const
{
    // Returns the viking special damage.
    return 40;
}

// Returns the viking special cooldown duration.
int Viking::SpecialCooldownTurns() const
{
    // Returns the viking cooldown length.
    return 4;
}

// Returns the viking special mana cost.
int Viking::SpecialManaCost() const
{
    // Returns the viking mana cost.
    return 60;
}

// Performs the viking special animation.
void Viking::SpecialAnimation() const
{
    // Outputs the special attack message.
    TypeOut(Name + ": Rage Smash.\n");
}

// Creates a fighter object based on the user’s class choice.
Character* CreateFighter(int choice, const string& name, Ninja* n, Pirate* p, Samurai* s, Viking* v)
{
    // Creates and returns a ninja if option one is selected.
    if (choice == 1) { *n = Ninja(name); return n; }

    // Creates and returns a pirate if option two is selected.
    if (choice == 2) { *p = Pirate(name); return p; }

    // Creates and returns a samurai if option three is selected.
    if (choice == 3) { *s = Samurai(name); return s; }

    // Creates and returns a viking if option four is selected.
    if (choice == 4) { *v = Viking(name); return v; }

    // Defaults to creating and returning a ninja if the choice is invalid.
    *n = Ninja(name);
    return n;
}