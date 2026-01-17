// Includes the duel function declarations and related interfaces.
#include "Duel.h"

// Includes utility functions such as TypeOut, random helpers, and formatting tools.
#include "Utilities.h"

// Allows use of standard library names without the std:: prefix.
using namespace std;

// Defines the maximum number of damage entries that can be tracked in a duel.
static const int MAX_ROUNDS = 120;

// Ensures that the two fighter names are not identical.
// The names are passed as pointers so they can be modified directly.
void ValidateDistinctNames(string* aName, string* bName)
{
    // Checks if both names are exactly the same.
    if (*aName == *bName)
    {
        // Appends a suffix to the second name to make it unique.
        *bName += " Two";

        // Notifies the user that a rename occurred.
        TypeOut("\nNames matched. Second fighter renamed to " + *bName + ".\n\n");
    }
}

// Calculates damage for a basic attack using randomness and difficulty scaling.
static int RollDamage(const Character* attacker, const int* difficulty)
{
    // Generates a random value between 0.0 and 1.0.
    double r = RngUnit();

    // Retrieves the base attack value from the attacker.
    int base = attacker->Attack();

    // Initializes the raw damage value.
    int raw = 0;

    // Determines the damage tier based on the random roll.
    if (r < 0.15) raw = 0;
    else if (r < 0.35) raw = base;
    else if (r < 0.55) raw = base + 5;
    else if (r < 0.80) raw = base + 10;
    else raw = base + 15;

    // Sets a default damage multiplier.
    double mult = 1.0;

    // Reduces damage on the easiest difficulty.
    if (*difficulty == 1) mult = 0.85;
    // Increases damage on the hardest difficulty.
    else if (*difficulty == 3) mult = 1.15;

    // Applies the multiplier to the raw damage.
    int scaled = static_cast<int>(raw * mult);

    // Ensures damage never becomes negative.
    if (scaled < 0) scaled = 0;

    // Returns the final scaled damage value.
    return scaled;
}

// Calculates damage for a special attack using special stats and randomness.
static int RollSpecialDamage(const Character* attacker, const int* difficulty)
{
    // Retrieves the base special damage from the attacker.
    int raw = attacker->SpecialDamage();

    // Adds a small random variance to the special damage.
    raw += RngInt(-3, 3);

    // Prevents negative damage values.
    if (raw < 0) raw = 0;

    // Sets a default damage multiplier.
    double mult = 1.0;

    // Adjusts damage for easier difficulty.
    if (*difficulty == 1) mult = 0.85;
    // Adjusts damage for harder difficulty.
    else if (*difficulty == 3) mult = 1.15;

    // Applies the multiplier to the damage.
    int scaled = static_cast<int>(raw * mult);

    // Ensures damage does not drop below zero.
    if (scaled < 0) scaled = 0;

    // Returns the final special damage value.
    return scaled;
}

// Applies damage to a target character by reducing its health.
static void ApplyHit(Character* target, const int* damage)
{
    // Retrieves the target current health.
    int hp = target->GetHealth();

    // Subtracts the damage amount.
    hp -= *damage;

    // Updates the target health safely.
    target->SetHealth(hp);
}

// Displays the current health, cooldown, and mana status of both fighters.
static void ShowStatus(const Character* a, const Character* b)
{
    // Outputs a blank line for spacing.
    TypeOut("\n");

    // Builds the formatted status line for the first fighter.
    string lineA =
        PadLeft(a->Name + " (" + a->ClassName() + ")", 24) +
        " " + HealthBar(a->GetHealth(), a->GetMaxHealth()) +
        " HP " + PadRightNumber(a->GetHealth(), 3) +
        "  CD (" + PadRightNumber(a->GetCooldown(), 2) + " turns)" +
        "  MP [" + to_string(a->GetMana()) + "/" + to_string(a->GetMaxMana()) + "]\n";

    // Builds the formatted status line for the second fighter.
    string lineB =
        PadLeft(b->Name + " (" + b->ClassName() + ")", 24) +
        " " + HealthBar(b->GetHealth(), b->GetMaxHealth()) +
        " HP " + PadRightNumber(b->GetHealth(), 3) +
        "  CD (" + PadRightNumber(b->GetCooldown(), 2) + " turns)" +
        "  MP [" + to_string(b->GetMana()) + "/" + to_string(b->GetMaxMana()) + "]\n";

    // Displays the first fighter status.
    TypeOut(lineA, 2);

    // Displays the second fighter status.
    TypeOut(lineB, 2);

    // Outputs a blank line for spacing.
    TypeOut("\n");
}

// Performs a basic attack animation depending on the attacker class.
static void PerformBasic(Character* attacker)
{
    // Executes the ninja basic attack animation if applicable.
    if (auto* n = dynamic_cast<Ninja*>(attacker)) n->ThrowStars();

    // Executes the pirate basic attack animation if applicable.
    if (auto* p = dynamic_cast<Pirate*>(attacker)) p->UseSword();

    // Executes the samurai basic animation if applicable.
    if (auto* s = dynamic_cast<Samurai*>(attacker)) s->SpecialAnimation();

    // Executes the viking basic animation if applicable.
    if (auto* v = dynamic_cast<Viking*>(attacker)) v->SpecialAnimation();
}

// Performs the special ability animation for a character.
static void PerformSpecial(Character* attacker)
{
    // Calls the polymorphic special animation function.
    attacker->SpecialAnimation();
}

// Determines whether the CPU should use a special ability this turn.
static bool CpuWantsSpecial(const Character* cpu)
{
    // Prevents special usage if the cooldown is active.
    if (!cpu->CanUseSpecial()) return false;

    // Prevents special usage if there is not enough mana.
    if (cpu->GetMana() < cpu->SpecialManaCost()) return false;

    // Uses a probability check to decide whether to use the special.
    return RngInt(1, 100) <= 45;
}

// Displays a summary of duel statistics for both fighters.
static void ShowDuelStats(const Character* a,
    const Character* b,
    const int* aHits,
    const int* bHits,
    const int* aCount,
    const int* bCount)
{
    // Prints the summary header.
    TypeOut("\nSummary\n", 4);

    // Handles statistics for the first fighter.
    if (*aCount == 0)
    {
        // Reports no damaging hits.
        TypeOut(a->Name + " landed no damaging hits.\n", 4);
    }
    else
    {
        // Initializes total and maximum hit tracking.
        int total = 0;
        int maxHit = 0;

        // Iterates through all recorded hits.
        for (int i = 0; i < *aCount; ++i)
        {
            // Adds damage to the total.
            total += aHits[i];

            // Updates the maximum hit if needed.
            if (aHits[i] > maxHit) maxHit = aHits[i];
        }

        // Calculates the average damage.
        double avg = static_cast<double>(total) / *aCount;

        // Outputs the calculated statistics.
        TypeOut(a->Name + " hits " + to_string(*aCount) +
            " total " + to_string(total) +
            " max " + to_string(maxHit) +
            " avg " + to_string(avg) + "\n", 4);
    }

    // Handles statistics for the second fighter.
    if (*bCount == 0)
    {
        // Reports no damaging hits.
        TypeOut(b->Name + " landed no damaging hits.\n", 4);
    }
    else
    {
        // Initializes total and maximum hit tracking.
        int total = 0;
        int maxHit = 0;

        // Iterates through all recorded hits.
        for (int i = 0; i < *bCount; ++i)
        {
            // Adds damage to the total.
            total += bHits[i];

            // Updates the maximum hit if needed.
            if (bHits[i] > maxHit) maxHit = bHits[i];
        }

        // Calculates the average damage.
        double avg = static_cast<double>(total) / *bCount;

        // Outputs the calculated statistics.
        TypeOut(b->Name + " hits " + to_string(*bCount) +
            " total " + to_string(total) +
            " max " + to_string(maxHit) +
            " avg " + to_string(avg) + "\n", 4);
    }
}

// Runs the full duel loop between two fighters.
void Duel(Character* a, Character* b, int* difficulty)
{
    // Resets both fighters health, mana, and cooldowns.
    a->ResetHealth();
    b->ResetHealth();

    // Initializes arrays to track damage per hit.
    int aHits[MAX_ROUNDS] = { 0 };
    int bHits[MAX_ROUNDS] = { 0 };

    // Initializes hit counters.
    int aCount = 0;
    int bCount = 0;

    // Allows both fighters to speak before the duel begins.
    a->Speak();
    b->Speak();

    // Displays the initial status of both fighters.
    ShowStatus(a, b);

    // Indicates whose turn it is.
    bool aTurn = true;

    // Continues the duel while both fighters are alive.
    while (a->GetHealth() > 0 && b->GetHealth() > 0)
    {
        // Handles the player turn.
        if (aTurn)
        {
            // Retrieves the mana cost for the special ability.
            int cost = a->SpecialManaCost();

            // Displays the player turn header.
            TypeOut("Turn " + a->Name + "\n", 2);

            // Displays the basic attack option.
            TypeOut("1 Basic attack\n", 2);

            // Builds the special ability menu line.
            string specialLine = "2 Special ability (" + to_string(cost) + "MP)";

            // Adds cooldown status if applicable.
            if (!a->CanUseSpecial()) specialLine += " (on cooldown)";

            // Adds mana warning if insufficient mana.
            if (a->GetMana() < cost) specialLine += " (not enough MP)";

            // Displays the special ability option.
            TypeOut(specialLine + "\n", 2);

            // Reads the player choice.
            int move = ReadIntChoice("Choose 1 or 2: ", 1, 2);

            // Waits for player confirmation.
            WaitForEnter("Press Enter to act. ");

            // Initializes damage dealt this turn.
            int dmg = 0;

            // Determines if the special ability can be used.
            bool canSpecial = a->CanUseSpecial() && (a->GetMana() >= cost);

            // Executes the chosen action.
            if (move == 2 && canSpecial)
            {
                // Performs the special animation.
                PerformSpecial(a);

                // Deducts mana for the special ability.
                a->SpendMana(cost);

                // Calculates special damage.
                dmg = RollSpecialDamage(a, difficulty);

                // Triggers the cooldown.
                a->TriggerCooldown();

                // Displays special damage output.
                TypeOut(string(a->SpecialName()) + " deals " + to_string(dmg) + ".\n", 6);
            }
            else
            {
                // Notifies the player if the special was unavailable.
                if (move == 2 && !canSpecial)
                {
                    TypeOut("Special not ready. Using basic attack.\n", 6);
                }

                // Performs the basic attack animation.
                PerformBasic(a);

                // Calculates basic attack damage.
                dmg = RollDamage(a, difficulty);

                // Displays hit or miss feedback.
                if (dmg == 0) TypeOut("Miss.\n", 6);
                else TypeOut("Hit for " + to_string(dmg) + ".\n", 6);
            }

            // Records the damage if applicable.
            if (dmg > 0 && aCount < MAX_ROUNDS)
                aHits[aCount++] = dmg;

            // Applies the damage to the opponent.
            ApplyHit(b, &dmg);

            // Displays updated status.
            ShowStatus(a, b);

            // Ends the duel if the opponent is defeated.
            if (b->GetHealth() == 0) break;
        }
        else
        {
            // Displays the CPU turn header.
            TypeOut("Turn " + b->Name + "\n", 2);

            // Waits before showing the CPU action.
            WaitForEnter("Press Enter to see the opponent act. ");

            // Initializes damage dealt this turn.
            int dmg = 0;

            // Determines whether the CPU uses a special ability.
            bool useSpecial = CpuWantsSpecial(b);

            // Executes the CPU chosen action.
            if (useSpecial)
            {
                // Retrieves the mana cost for the special.
                int cost = b->SpecialManaCost();

                // Performs the special animation.
                PerformSpecial(b);

                // Deducts mana for the special ability.
                b->SpendMana(cost);

                // Calculates special damage.
                dmg = RollSpecialDamage(b, difficulty);

                // Triggers the cooldown.
                b->TriggerCooldown();

                // Displays special damage output.
                TypeOut(string(b->SpecialName()) + " deals " + to_string(dmg) + ".\n", 6);
            }
            else
            {
                // Performs the basic attack animation.
                PerformBasic(b);

                // Calculates basic attack damage.
                dmg = RollDamage(b, difficulty);

                // Displays hit or miss feedback.
                if (dmg == 0) TypeOut("Miss.\n", 6);
                else TypeOut("Hit for " + to_string(dmg) + ".\n", 6);
            }

            // Records the damage if applicable.
            if (dmg > 0 && bCount < MAX_ROUNDS)
                bHits[bCount++] = dmg;

            // Applies the damage to the player.
            ApplyHit(a, &dmg);

            // Displays updated status.
            ShowStatus(a, b);

            // Ends the duel if the player is defeated.
            if (a->GetHealth() == 0) break;
        }

        // Advances cooldowns and regenerates mana for both fighters.
        a->TickCooldown();
        b->TickCooldown();

        // Switches turns.
        aTurn = !aTurn;

        // Adds a short pause for pacing.
        PauseMs(200);
    }

    // Defines the path used to store persistent fighter statistics.
    string statsPath = "fighter_stats.txt";

    // Handles the draw condition.
    if (a->GetHealth() == 0 && b->GetHealth() == 0)
    {
        TypeOut("Draw.\n", 8);
    }
    // Handles the case where the player loses.
    else if (a->GetHealth() == 0)
    {
        TypeOut(b->Name + " wins.\n", 8);
        AddWin(statsPath, b->Name);
        AddLoss(statsPath, a->Name);
    }
    // Handles the case where the player wins.
    else
    {
        TypeOut(a->Name + " wins.\n", 8);
        AddWin(statsPath, a->Name);
        AddLoss(statsPath, b->Name);
    }

    // Displays the final duel statistics.
    ShowDuelStats(a, b, aHits, bHits, &aCount, &bCount);
}