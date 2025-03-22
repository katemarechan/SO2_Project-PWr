#include <array>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>


#include "philosopher.h"

// Number of philosophers and chopsticks
#define NUM_PHILOSOPHERS 5

// Global variables
std::array<Philosopher*, NUM_PHILOSOPHERS> philosophers;
std::array<Chopstick*, NUM_PHILOSOPHERS> chopsticks;
std::mutex console_mutex; // Mutex for console output

// Names of philosophers
std::array<std::string, NUM_PHILOSOPHERS> names = {
        "Plato",
        "Socrates",
        "Kant",
        "Descartes",
        "Confucius"
};

// Identifiers for display
std::array<std::string, NUM_PHILOSOPHERS> identifiers = {
        "[P]", // Plato
        "[S]", // Socrates
        "[K]", // Kant
        "[D]", // Descartes
        "[C]"  // Confucius
};

/**
 * Display a visualization of the table arrangement
 */
void visualizeArrangement() {
    std::cout << "\n=== Table Arrangement Visualization ===" << std::endl;
    std::cout << "    Chopstick 0" << std::endl;
    std::cout << "       /   \\" << std::endl;
    std::cout << "Philosopher 0  Philosopher 1" << std::endl;
    std::cout << "     /           \\" << std::endl;
    std::cout << "Chopstick 4    Chopstick 1" << std::endl;
    std::cout << "     \\           /" << std::endl;
    std::cout << "Philosopher 4  Philosopher 2" << std::endl;
    std::cout << "       \\     /" << std::endl;
    std::cout << "      Chopstick 3  Chopstick 2" << std::endl;
    std::cout << "           \\  /" << std::endl;
    std::cout << "        Philosopher 3" << std::endl;
}

/**
 * Signal handler for Ctrl+C
 * Stops all philosophers gracefully
 */
void quit(int signal) {
    std::cout << "\n=== Dinner is over! Philosophers finishing... ===" << std::endl;

    // Tell all philosophers to stop
    for (Philosopher* p : philosophers) {
        p->stop();
    }
}

/**
 * Main function
 */
int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "=== Dining Philosophers Problem Simulation ===" << std::endl;
    std::cout << "Press Ctrl+C to end the dinner" << std::endl;
    std::cout << "Each philosopher will eat 5 times" << std::endl;

    // Create chopsticks with numeric IDs
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        chopsticks[i] = new Chopstick("Chopstick " + std::to_string(i), i);
    }

    // Create philosophers and assign chopsticks
    std::cout << "\n=== Philosophers at the table: ===" << std::endl;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        // Each philosopher takes the chopstick to their left and right
        // For philosopher i, left chopstick is i, right chopstick is (i+1)%NUM_PHILOSOPHERS
        int left_idx = i;
        int right_idx = (i + 1) % NUM_PHILOSOPHERS;

        // Create the philosopher with identifier prefix
        philosophers[i] = new Philosopher(
                identifiers[i] + " " + names[i],
                5, // appetite - how many times they need to eat
                *chopsticks[left_idx],
                *chopsticks[right_idx],
                console_mutex
        );
    }

    // Display the arrangement
    visualizeArrangement();

    // Show chopstick assignments
    std::cout << "\n=== Chopstick assignments: ===" << std::endl;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        std::cout << identifiers[i] + " " + names[i] <<
                  " has chopsticks " << i << " (left, ID: " << chopsticks[i]->getIdNum() <<
                  ") and " << (i + 1) % NUM_PHILOSOPHERS <<
                  " (right, ID: " << chopsticks[(i + 1) % NUM_PHILOSOPHERS]->getIdNum() <<
                  ")" << std::endl;
    }

    // Set up signal handler for Ctrl+C
    signal(SIGINT, quit);

    std::cout << "\n=== Dinner has started! ===" << std::endl;

    // Wait for all philosophers to finish
    for (Philosopher* p : philosophers) {
        p->join();
    }

    std::cout << "\n=== Everyone has finished eating! ===" << std::endl;

    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        delete philosophers[i];
        delete chopsticks[i];
    }

    return 0;
}