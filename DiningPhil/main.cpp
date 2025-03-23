#include <array>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <memory>
#include <vector> 

#include "philosopher.h"

// Number of philosophers and chopsticks
#define NUM_PHILOSOPHERS 5

// Global variables
// Changed from fixed arrays to vectors for dynamic sizing (before were arrays, bc the number was fixed (5))
std::vector<std::unique_ptr<Philosopher>> philosophers;
std::vector<std::unique_ptr<Chopstick>> chopsticks;
std::mutex console_mutex; // Mutex for console output

// Names of default 5 philosophers
std::array<std::string, DEFAULT_PHILOSOPHERS> defaultNames  = {
        "Plato",
        "Socrates",
        "Kant",
        "Descartes",
        "Confucius"
};

// Identifiers for display
std::array<std::string, DEFAULT_PHILOSOPHERS> defaultIdentifiers = {
        "[P]", // Plato
        "[S]", // Socrates
        "[K]", // Kant
        "[D]", // Descartes
        "[C]"  // Confucius
};

/**
 * Display a visualization of the table arrangement for 5 philosophers
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
 */
void quit(int signal) {
    std::cout << "\n=== Dinner is over! Philosophers finishing... ===" << std::endl;

    // Tell all philosophers to stop
    for (Philosopher* p : philosophers) {
        p->stop();
    }
}

//main 
int main() {
    // Seed the random number generator (used for the amount of time to think and time to eat)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::cout << "=== Dining Philosophers Problem Simulation ===" << std::endl;
    std::cout << "Press Ctrl+C to end the dinner" << std::endl;
    
    // Mode selection for custom or default n. of phil.
    int choice;
    std::cout << "\nSelect an option:" << std::endl;
    std::cout << "1. Run with 5 philosophers (with visualization)" << std::endl;
    std::cout << "2. Run with custom number of philosophers" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    int numPhilosophers;
    bool showVisualization = false;   //(true only for 5 phil.) 

// Handler for choices
   if (choice == 1) {
        numPhilosophers = DEFAULT_PHILOSOPHERS;
        showVisualization = true;
    } else if (choice == 2) {
        std::cout << "Enter the number of philosophers: ";
        std::cin >> numPhilosophers;

        if (numPhilosophers <= 0) {
            std::cout << "Invalid number of philosophers. Using default (5)." << std::endl;
            numPhilosophers = DEFAULT_PHILOSOPHERS;
        }
    } else {
        std::cout << "Invalid choice. Using default (5 philosophers with visualization)." << std::endl;
        numPhilosophers = DEFAULT_PHILOSOPHERS;
        showVisualization = true;
    }

    std::cout << "Each philosopher will eat 5 times" << std::endl;

   // Resize vectors to accommodate the specified number of philosophers 
    philosophers.resize(numPhilosophers);
    chopsticks.resize(numPhilosophers);

    // Create chopsticks with numeric IDs
    for (int i = 0; i < numPhilosophers; i++) {
        chopsticks[i] = std::make_unique<Chopstick>("Chopstick " + std::to_string(i), i);
    }

   // Create philosophers and assign chopsticks
    std::cout << "\n=== Philosophers at the table: ===" << std::endl;
    for (int i = 0; i < numPhilosophers; i++) {
        // Each philosopher takes the chopstick to their left and right
        // For philosopher i, left chopstick is i, right chopstick is (i+1)%numPhilosophers
        int left_idx = i;
        int right_idx = (i + 1) % numPhilosophers;

        // Generate philosopher name and identifier
        std::string name, identifier;

        if (i < DEFAULT_PHILOSOPHERS) {
            // Use default names for the first 5 philosophers
            name = defaultNames[i];
            identifier = defaultIdentifiers[i];
        } else {
            // Use generic names for additional philosophers (didnt want to make a database/list with names, since one can request a number of philisophers to be 100 for example...)
            name = "Phil. " + std::to_string(i + 1);
            identifier = "[" + std::to_string(i + 1) + "]";
        }

        // Create philosopher
        philosophers[i] = std::make_unique<Philosopher>(
                identifier + " " + name,
                5, // appetite - how many times they need to eat
                *chopsticks[left_idx],
                *chopsticks[right_idx],
                console_mutex
        );
    }

   // Display the arrangement if requested
    if (showVisualization) {
        visualizeArrangement();
    }

    // Show chopstick assignments
    std::cout << "\n=== Chopstick assignments: ===" << std::endl;
    for (int i = 0; i < numPhilosophers; i++) {
        std::string philosopher_name;
        if (i < DEFAULT_PHILOSOPHERS) {
            philosopher_name = defaultIdentifiers[i] + " " + defaultNames[i];
        } else {
            philosopher_name = "[" + std::to_string(i + 1) + "] Phil. " + std::to_string(i + 1);
        }

        std::cout << philosopher_name <<
                  " has chopsticks " << i << " (left, ID: " << chopsticks[i]->getIdNum() <<
                  ") and " << (i + 1) % numPhilosophers <<
                  " (right, ID: " << chopsticks[(i + 1) % numPhilosophers]->getIdNum() <<
                  ")" << std::endl;
    }

    // Set up signal handler for Ctrl+C
    signal(SIGINT, quit);

    std::cout << "\n=== Dinner has started! ===" << std::endl;
    //Shows the process of eating
    // Wait for all philosophers to finish
    for (auto& p : philosophers) {
        p->join();
    }

    std::cout << "\n=== Everyone has finished eating! ===" << std::endl;

    return 0;
}
