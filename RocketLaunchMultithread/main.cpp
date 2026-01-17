#include <iostream>                 // Includes the iostream library for console input and output.
#include <thread>                   // Includes the thread library to enable multithreading.
#include <mutex>                    // Includes mutex tools for thread synchronization.
#include <atomic>                   // Includes atomic types for thread-safe shared variables.
#include <condition_variable>       // Includes condition variables for thread signaling.
#include <chrono>                   // Includes time utilities for delays.
#include <string>                   // Includes the string class for text handling.
#include <conio.h>                  // Includes console I/O functions such as _kbhit and _getch (Windows only).

std::mutex coutMutex;               // Creates a mutex to safely control access to console output.
std::mutex controlMutex;            // Creates a mutex for controlling launch authority transfers.
std::condition_variable controlTransferredCv;  // Condition variable used to signal when launch control transfers.

std::atomic<bool> abortRequested{ false }; // Atomic boolean indicating whether an abort has been requested.
bool controlTransferred = false;           // Flag that indicates when Space Cadet takes control after Rocket 1.
int rocketsLaunched = 0;                   // Counter for total successful rocket launches.

void safePrint(const std::string& text)
{
    std::lock_guard<std::mutex> lock(coutMutex); // Locks the console output to ensure safe multi-threaded printing.
    std::cout << text << std::endl;              // Prints the provided message to the console.
}

void clearKeyBuffer()
{
    while (_kbhit())      // Checks if any keyboard input is waiting in the buffer.
        _getch();         // Removes that input so old Enter presses do not activate future prompts.
}

bool waitForUser(int rocketNum)
{
    clearKeyBuffer();     // Clears any leftover input so the user must press Enter only once.

    {
        std::lock_guard<std::mutex> lock(coutMutex);      // Locks printing to prevent output overlap.
        std::cout << "\nPress Enter to launch Rocket "    // Prints instructions for launching.
            << rocketNum
            << " or type 'a' and press Enter to abort: ";
    }

    std::string input;                 // Stores the user’s entered text.
    std::getline(std::cin, input);     // Reads the full line of user input.

    if (!input.empty() && (input[0] == 'a' || input[0] == 'A')) // Checks whether the user typed 'a'.
    {
        abortRequested.store(true);    // Sets the abort flag to true.
        safePrint("[Main Base] Abort signal triggered. Stopping launches."); // Prints a confirmation.
        return false;                  // Returns false to indicate the launch should not proceed.
    }

    return true;                       // User pressed Enter, so the launch may proceed.
}

void launchRocketFromMainBase()
{
    safePrint("\n[Main Base] Rocket 1 will auto launch..."); // Announces automatic launch of Rocket 1.
    safePrint("[Main Base] Launching Rocket 1...");           // Marks the beginning of the launch sequence.

    std::this_thread::sleep_for(std::chrono::seconds(3));    // Waits three seconds to simulate a launch delay.

    rocketsLaunched++;                                        // Increments the launch count.
    safePrint("[Main Base] Rocket 1 launch successful");      // Confirms launch success.

    {
        std::lock_guard<std::mutex> lock(controlMutex);       // Locks control flag modification.
        controlTransferred = true;                            // Transfers control to the Space Cadet.
    }

    safePrint("[Main Base] Control transferred to Space Cadet");  // Prints transfer confirmation.
    controlTransferredCv.notify_one();                           // Signals the Space Cadet thread to proceed.
}

void spaceCadetController()
{
    {
        std::unique_lock<std::mutex> lock(controlMutex);      // Locks while waiting for control transfer.
        controlTransferredCv.wait(lock, [] {                  // Waits until control is transferred or abort occurs.
            return controlTransferred || abortRequested.load();
            });
    }

    if (abortRequested.load())                                // Checks if abort was requested before launching.
    {
        safePrint("[Space Cadet] Abort received before I started launching."); // Prints abort message.
        return;                                               // Stops execution of this thread.
    }

    for (int rocket = 2; rocket <= 10; ++rocket)              // Loops through rockets 2 through 10.
    {
        if (!waitForUser(rocket))                             // Waits for user's Enter press or abort.
        {
            safePrint("[Space Cadet] Abort override received. Ending launch sequence."); // Prints halt notice.
            return;                                           // Stops launching additional rockets.
        }

        safePrint("[Space Cadet] Launching Rocket " + std::to_string(rocket) + "..."); // Announces launch.
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulates launch ignition time.

        rocketsLaunched++;                                    // Updates total rocket count.
        safePrint("[Space Cadet] Rocket " + std::to_string(rocket) + " launch successful"); // Confirms launch.

        if (abortRequested.load())                            // Checks if an abort has been triggered mid-sequence.
        {
            safePrint("[Space Cadet] Abort signal detected. Stopping launches."); // Prints abort message.
            return;                                           // Ends launch operations.
        }
    }

    safePrint("[Space Cadet] All scheduled rockets successfully launched."); // Indicates mission success.
}

int main()
{
    safePrint("===============================================");    // Prints header section.
    safePrint("      Multithreaded Rocket Launch Control      ");    // Prints program title.
    safePrint("===============================================");    // Prints divider.

    safePrint("\nInstructions:");                                   // Explains program operation.
    safePrint("Rocket 1 auto launches from Main Base.");
    safePrint("After Rocket 1, control transfers to the Space Cadet.");
    safePrint("You must press Enter to launch each remaining rocket.");
    safePrint("Type 'a' and press Enter to abort all future launches.");
    safePrint("Each launch includes a 3 second ignition countdown.");
    safePrint("===============================================");    // Prints closing divider.

    std::this_thread::sleep_for(std::chrono::seconds(1));           // Allows time for user to read instructions.

    std::thread t1(launchRocketFromMainBase);                       // Creates a thread to launch Rocket 1.
    std::thread t2(spaceCadetController);                           // Creates a thread for Space Cadet control.

    t1.join();                                                      // Waits for the Main Base thread to finish.
    t2.join();                                                      // Waits for the Space Cadet thread to finish.

    safePrint("\n[Main Base] Final report: "                        // Prints total successful rockets.
        + std::to_string(rocketsLaunched)
        + " rocket(s) launched.");

    safePrint("Mission complete, press Enter to exit.");            // Prompts user to end the program.
    std::string dummy;                                              // Temp variable for final Enter.
    std::getline(std::cin, dummy);                                  // Waits for final user input.

    return 0;                                                       // Ends program successfully.
}