#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <ctime>
#include "chopstick.h"

/**
 * Philosopher class
 * Represents a philosopher in the dining philosophers problem
 * Each philosopher thinks and eats in cycles
 */
class Philosopher {
private:
    std::string name;             // Philosopher's name
    int appetite;                 // How many times the philosopher needs to eat
    int food_eaten;               // How many times the philosopher has eaten
    Chopstick& left_chopstick;    // Left chopstick
    Chopstick& right_chopstick;   // Right chopstick
    std::mutex& g_lock;           // Global lock for console output
    std::thread td;               // Thread for the philosopher's actions
    bool stopped;                 // Flag to stop the philosopher
    std::mt19937 rng{std::random_device{}()}; // Random number generator

    // The main function that runs in the thread
    void run();

    // Print a message from the philosopher
    void print(std::string str);

    // Make the philosopher wait for a random time
    void ponder(int min_sec, int max_sec);

public:
    // Constructor
    Philosopher(std::string name, int appetite, Chopstick& left_stick,
                Chopstick& right_stick, std::mutex& g_lock);

    // Destructor
    ~Philosopher();

    // Make the philosopher eat
    void eat();

    // Make the philosopher think
    void think();

    // Start the philosopher's thread
    void start();

    // Signal the philosopher to stop
    void stop();

    // Wait for the philosopher's thread to finish
    void join();
};

#endif // PHILOSOPHER_HPP