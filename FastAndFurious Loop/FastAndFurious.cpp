// FastAndFuriousSim.cpp // file name for the program source
// Expanded Interactive Console Story  Fast and Furious Theme // short description of the program theme
// Practice input and output and data processing and branching and user experience // learning goals for this file

#include <iostream> // include standard input output library
#include <string> // include string support
#include <vector> // include vector support
#include <limits> // include numeric limits for input clearing
#include <cstdlib> // include general utilities like rand and srand
#include <ctime> // include time for random seed

using namespace std; // use the standard namespace to avoid std prefix

void clearInput() { // function to clean the input stream
    cin.clear(); // clear error flags on cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the rest of the current input line
} // end of clearInput

int readInt(const string& prompt) { // read any integer with a prompt and validation
    while (true) { // loop until valid input is read
        cout << prompt; // show the prompt to the user
        int x; // variable to hold the number typed by the user
        if (cin >> x) { // if reading an integer succeeded
            clearInput(); // clear leftover input including newline
            return x; // return the valid integer
        } // end if successful read
        clearInput(); // clear bad input and flush the line
        cout << "Please enter a whole number.\n"; // tell the user the input must be a whole number
    } // end while loop
} // end of readInt

int readIntRange(const string& prompt, int a, int b) { // read an integer that must be within a range
    while (true) { // loop until a valid number in range is read
        int x = readInt(prompt); // read an integer using the helper
        if (x >= a && x <= b) return x; // if x is in range return it
        cout << "Choose between " << a << " and " << b << ".\n"; // tell the user the valid range
    } // end while loop
} // end of readIntRange

string readLine(const string& prompt) { // read a full line of text including spaces
    cout << prompt; // show the prompt
    string s; // variable to hold the input line
    getline(cin, s); // read the full line into s
    return s; // return the text
} // end of readLine

void beat() { cout << "\n"; } // print a blank line for pacing in the console

//  State to track choices and results // header for the state structure
struct State { // structure to hold the full game state
    string plrName; // player name
    string crewDriver; // chosen driver
    string groupTech; // chosen tech expert
    string crewMuscle; // chosen muscle
    string crewInfil; // chosen infiltrator
    string crewStrat; // chosen strategist
    int totRisk = 0; // total risk value starts at zero
    int totHeat = 0; // total heat value starts at zero
    int totTrust = 0; // team trust value starts at zero
    int totCash = 0; // total cash value starts at zero
}; // end of State

//  TEAM DRAFT // header for the team selection section
void chooseTeam(State& st) { // function to pick crew members and adjust stats
    cout << "Choose your DRIVER:\n1.Dom  2.Brian  3.Letty  4.Han\n"; // show driver choices
    switch (readIntRange("Choice: ", 1, 4)) { // get driver choice from one to four
    case 1: st.crewDriver = "Dom"; st.totTrust += 2; break; // choose Dom and raise trust
    case 2: st.crewDriver = "Brian"; st.totTrust += 1; break; // choose Brian and raise trust a bit
    case 3: st.crewDriver = "Letty"; st.totRisk -= 1; break; // choose Letty and lower risk
    case 4: st.crewDriver = "Han"; st.totTrust += 1; st.totRisk -= 1; break; // choose Han and adjust trust and risk
    } // end switch for driver

    cout << "Choose your TECH:\n1.Tej  2.Mia  3.Ramsey\n"; // show tech choices
    switch (readIntRange("Choice: ", 1, 3)) { // get tech choice from one to three
    case 1: st.groupTech = "Tej"; st.totRisk -= 2; break; // choose Tej and lower risk
    case 2: st.groupTech = "Mia"; st.totTrust += 1; break; // choose Mia and raise trust
    case 3: st.groupTech = "Ramsey"; st.totTrust += 2; break; // choose Ramsey and raise trust more
    } // end switch for tech

    cout << "Choose your MUSCLE:\n1.Hobbs  2.Roman  3.Shaw\n"; // show muscle choices
    switch (readIntRange("Choice: ", 1, 3)) { // get muscle choice from one to three
    case 1: st.crewMuscle = "Hobbs"; st.totHeat += 1; break; // choose Hobbs and raise heat
    case 2: st.crewMuscle = "Roman"; st.totTrust += 1; break; // choose Roman and raise trust
    case 3: st.crewMuscle = "Shaw"; st.totRisk -= 1; st.totHeat += 1; break; // choose Shaw and adjust risk and heat
    } // end switch for muscle

    cout << "Choose your INFILTRATOR:\n1.Gisele  2.Suki  3.Han\n"; // show infiltrator choices
    switch (readIntRange("Choice: ", 1, 3)) { // get infiltrator choice from one to three
    case 1: st.crewInfil = "Gisele"; st.totRisk -= 2; break; // choose Gisele and lower risk
    case 2: st.crewInfil = "Suki"; st.totHeat -= 1; break; // choose Suki and lower heat
    case 3: st.crewInfil = "Han"; st.totTrust += 1; break; // choose Han and raise trust
    } // end switch for infiltrator

    cout << "Choose your STRATEGIST:\n1.Dom  2.Brian  3.Shaw\n"; // show strategist choices
    switch (readIntRange("Choice: ", 1, 3)) { // get strategist choice from one to three
    case 1: st.crewStrat = "Dom"; st.totTrust += 2; break; // choose Dom and raise trust more
    case 2: st.crewStrat = "Brian"; st.totRisk -= 1; break; // choose Brian and lower risk
    case 3: st.crewStrat = "Shaw"; st.totHeat += 1; break; // choose Shaw and raise heat
    } // end switch for strategist

    beat(); // add a blank line after selection
} // end of chooseTeam

//  PLANNING PHASE // header for plan setup
void planning(State& st) { // function to pick plan details
    cout << "Pick ENTRY METHOD:\n1.Silent  2.Decoy  3.Full send  4.Rooftop drop\n"; // show entry options
    int e = readIntRange("Choice: ", 1, 4); // read entry choice
    if (e == 1) { st.totRisk -= 2; st.totCash += 100000; } // silent lowers risk and adds cash
    if (e == 2) { st.totHeat += 1; st.totTrust += 1; st.totCash += 90000; } // decoy raises heat and trust and adds cash
    if (e == 3) { st.totRisk += 2; st.totHeat += 2; st.totCash += 130000; } // bold entry raises risk and heat and adds more cash
    if (e == 4) { st.totRisk -= 1; st.totCash += 110000; } // rooftop drop lowers risk and adds cash

    cout << "Pick VEHICLE:\n1.Muscle  2.Tuner  3.Rally  4.Stealth van\n"; // show vehicle options
    int v = readIntRange("Choice: ", 1, 4); // read vehicle choice
    if (v == 1) { st.totHeat += 2; st.totTrust += 1; } // muscle raises heat and trust
    if (v == 2) { st.totRisk -= 1; } // tuner lowers risk
    if (v == 3) { st.totRisk -= 1; st.totHeat -= 1; } // rally lowers risk and heat
    if (v == 4) { st.totRisk -= 2; } // stealth van lowers risk more

    cout << "Pick ROUTE:\n1.Freeway  2.Side streets  3.River road  4.Metro tunnel\n"; // show route options
    int r = readIntRange("Choice: ", 1, 4); // read route choice
    if (r == 1) { st.totHeat += 2; st.totCash += 20000; } // freeway is fast but hot and adds cash
    if (r == 2) { st.totRisk -= 1; } // side streets lower risk
    if (r == 3) { st.totRisk += 1; st.totHeat -= 1; st.totCash += 10000; } // river road trades risk and heat and adds cash
    if (r == 4) { st.totRisk -= 2; st.totHeat += 1; } // metro tunnel lowers risk but raises heat a bit

    cout << "Pick DISGUISE:\n1.Security  2.Work crew  3.Media film crew  4.Street racers\n"; // show disguise options
    int d = readIntRange("Choice: ", 1, 4); // read disguise choice
    if (d == 1) { st.totRisk -= 1; } // security lowers risk a bit
    if (d == 2) { st.totRisk -= 2; } // work crew lowers risk more
    if (d == 3) { st.totHeat += 1; st.totCash += 5000; } // media raises heat and adds cash
    if (d == 4) { st.totHeat += 2; st.totTrust += 1; } // racers raise heat but raise trust

    cout << "Pick TIME:\n1.Midnight  2.Sunrise  3.Rush hour  4.Storm night\n"; // show time options
    int t = readIntRange("Choice: ", 1, 4); // read time choice
    if (t == 1) { st.totRisk -= 1; st.totHeat -= 1; } // midnight lowers risk and heat
    if (t == 2) { st.totTrust += 1; } // sunrise raises trust
    if (t == 3) { st.totHeat += 2; st.totCash += 3000; } // rush hour raises heat and adds cash
    if (t == 4) { st.totRisk += 1; st.totHeat -= 2; } // storm night raises risk but lowers heat

    beat(); // add spacing after planning
} // end of planning

//  RANDOM EVENTS DURING JOB // header for events
void randomEvent(State& st) { // function to apply a random twist during the job
    int roll = rand() % 100; // random value from zero to ninety nine
    if (roll < 20) { // if the value is in the first fifth
        cout << "A police chopper locks on. Tej scrambles a jammer.\n"; // describe the event
        st.totHeat += 2; // raise heat due to the chopper
        st.totRisk += 1; // raise risk due to pressure
    } // end branch one
    else if (roll < 40) { // second fifth
        cout << "A drawbridge rises ahead. Dom yells and jumps it.\n"; // describe the event
        st.totTrust += 1; st.totRisk += 1; // raise trust for bold drive and raise risk for the jump
    } // end branch two
    else if (roll < 60) { // third fifth
        cout << "Rival gang cars appear. Hobbs clears them.\n"; // describe the event
        st.totHeat += 1; st.totCash += 20000; // more heat but gain extra cash
    } // end branch three
    else if (roll < 80) { // fourth fifth
        cout << "Han finds a shortcut alley.\n"; // describe the event
        st.totRisk -= 2; // lower risk due to the shortcut
    } // end branch four
    else { // last fifth
        cout << "Ramsey hacks traffic lights green.\n"; // describe the event
        st.totRisk -= 1; st.totHeat -= 1; // lower risk and heat due to better lights
    } // end branch five
    beat(); // add a blank line after the event
} // end of randomEvent

//  JOB EXECUTION // header for the run section
void jobRun(State& st) { // run the main action and take choices
    cout << "Engines roar. Tires spin. The job is live.\n"; // describe the start of the job
    beat(); // blank line for pacing

    cout << "Blocked by a semi:\n1.Nudge through  2.Duck into loading bay  3.Ramp over car hauler\n"; // show obstacle choices
    int a = readIntRange("Move: ", 1, 3); // read the move choice
    if (a == 1) st.totHeat += 1; // nudging raises heat
    if (a == 2) st.totRisk -= 1; // loading bay lowers risk
    if (a == 3) { st.totRisk += 1; st.totTrust += 1; } // ramp raises risk and trust

    beat(); // spacing after the first choice

    cout << "Cops on radio sweep.\n1.Go dark through tunnel  2.Roman distracts with fireworks  3.Split team\n"; // show next choices
    int b = readIntRange("Plan: ", 1, 3); // read the plan choice
    if (b == 1) st.totRisk -= 1; // going dark lowers risk
    if (b == 2) { st.totHeat += 2; st.totTrust += 1; } // fireworks raise heat and trust
    if (b == 3) { st.totRisk += 1; st.totCash += 10000; } // split raises risk and adds cash

    beat(); // spacing before random events
    randomEvent(st); // trigger the first random event
    randomEvent(st); // trigger the second random event
} // end of jobRun

//  ENDING // header for the outcome
void ending(const State& st) { // show final stats and outcome
    cout << "Trust " << st.totTrust << "  Risk " << st.totRisk << "  Heat " << st.totHeat << "  Cash $" << st.totCash << "\n\n"; // print final numbers

    if (st.totTrust >= 4 && st.totRisk <= 0 && st.totHeat <= 1) // best outcome check
        cout << "Perfect run. Clean exit. Dom smiles and says: \"Family.\"\n"; // print best ending
    else if (st.totHeat >= 5) // very high heat outcome
        cout << "Police flood the area. You ditch the cars in the river and hide out in Rio.\n"; // print hot ending
    else if (st.totRisk >= 5) // very high risk outcome
        cout << "Risk went off the charts. A crash ends the run early.\n"; // print crash ending
    else if (st.totTrust <= 0) // very low trust outcome
        cout << "Crew tension broke the plan. The team walks away quietly.\n"; // print split ending
    else // default solid outcome
        cout << "Solid score. You slip away, a little messy but rich.\n"; // print normal ending
} // end of ending

//  GAME LOOP // header for the main loop
void play() { // run one full session
    State st; // create a fresh game state
    st.plrName = readLine("Enter your name: "); // ask for player name
    if (st.plrName.empty()) st.plrName = "Driver"; // default name if the user pressed enter

    chooseTeam(st); // run team selection
    planning(st); // run plan setup
    jobRun(st); // run the action
    ending(st); // show the result
} // end of play

int main() { // program entry point
    srand((unsigned)time(0)); // seed the random generator with current time
    cout << "FAST & FURIOUS: Interactive Story\n\n"; // title banner

    bool again = true; // control the replay loop
    while (again) { // play at least one time, then ask to play again
        play(); // run one full game

        // robust, simple choice for replay
        int r = readIntRange("\nPlay again? 1.Yes  2.No: ", 1, 2); // accept 1 or 2 only
        again = (r == 1); // 1 means yes, 2 means no
        beat(); // space between runs for clean UX
    }

    cout << "Thanks for playing.\n"; // friendly exit
    return 0; // end program
}