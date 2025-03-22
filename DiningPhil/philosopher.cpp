#include "philosopher.h"
#include <iostream>
#include <chrono>


/**
 * Constructor for Philosopher
 * @param name The philosopher's name
 * @param appetite How many times the philosopher needs to eat
 * @param left_stick Left chopstick
 * @param right_stick Right chopstick
 * @param g_lock Global mutex for console output
 */
Philosopher::Philosopher(std::string name, int appetite, Chopstick& left_stick,
                         Chopstick& right_stick, std::mutex& g_lock)
        : name(name),
          appetite(appetite),
          left_chopstick(left_stick),
          right_chopstick(right_stick),
          g_lock(g_lock),
          td(&Philosopher::run, this) {

    food_eaten = 0;
    stopped = false;
    print("has joined the table");
}

/**
 * Destructor for Philosopher
 */
Philosopher::~Philosopher() {
    print("is leaving the table");
}

/**
 * Make the philosopher eat
 * Uses the resource hierarchy solution to prevent deadlock
 */
void Philosopher::eat() {
    // Let everyone know we're trying to eat
    print("hungry and waiting for chopsticks");

    // Resource hierarchy solution:
    // Always pick up the lower-numbered chopstick first
    // This prevents the circular wait condition needed for deadlock
    Chopstick* first;
    Chopstick* second;

    if (left_chopstick.getIdNum() < right_chopstick.getIdNum()) {
        first = &left_chopstick;
        second = &right_chopstick;
    } else {
        first = &right_chopstick;
        second = &left_chopstick;
    }

    // Take first chopstick (lower ID)
    {
        std::lock_guard<std::mutex> first_lock(first->mtx);
        print("picked up chopstick " + std::to_string(first->getIdNum()));

        // Small delay to make the issue more visible if it exists
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Take second chopstick (higher ID)
        std::lock_guard<std::mutex> second_lock(second->mtx);
        print("picked up chopstick " + std::to_string(second->getIdNum()));

        // Now we have both chopsticks, eat!
        food_eaten++;
        print("eating meal " + std::to_string(food_eaten) + "/" + std::to_string(appetite));

        // Spend some time eating
        ponder(1, 2);

        // Locks are automatically released when we leave this scope
        print("put down chopsticks " + std::to_string(first->getIdNum()) +
              " and " + std::to_string(second->getIdNum()));
    }
}

/**
 * Make the philosopher think
 */
void Philosopher::think() {
    print("thinking");

    // Spend some time thinking
    ponder(1, 2);
}

/**
 * Make the philosopher wait for a random time
 * @param min_sec Minimum time in seconds
 * @param max_sec Maximum time in seconds
 */
void Philosopher::ponder(int min_sec, int max_sec) {
    if (stopped) return;

    // Generate a random duration between min_sec and max_sec
    std::uniform_int_distribution<> dist(min_sec, max_sec);
    int seconds = dist(rng);

    // Sleep for that duration
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    // Check if we've eaten enough
    if (food_eaten >= appetite) {
        stopped = true;
    }
}

/**
 * Print a message from the philosopher
 * @param str The message to display
 */
void Philosopher::print(std::string str) {
    // Lock the console so output doesn't get mixed up
    std::lock_guard<std::mutex> cout_lock(g_lock);

    // Get current time for timestamp
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    // Format: [HH:MM:SS] Name: Action
    char time_str[9];
    std::strftime(time_str, sizeof(time_str), "%H:%M:%S", std::localtime(&time));

    std::cout << "[" << time_str << "] " << name << ": " << str << std::endl;
}

/**
 * Signal the philosopher to stop
 */
void Philosopher::stop() {
    stopped = true;
}

/**
 * The main function that runs in the thread
 * Alternates between thinking and eating until stopped
 */
void Philosopher::run() {
    // Small initial delay to stagger the philosophers
    std::this_thread::sleep_for(std::chrono::milliseconds(200 * (rand() % 10)));

    // Main loop
    while (!stopped) {
        think();
        if (stopped) break;
        eat();
    }

    print("satisfied and stops eating");
}

/**
 * Wait for the philosopher's thread to finish
 */
void Philosopher::join() {
    if (td.joinable()) {
        td.join();
    }
}