#ifndef CHOPSTICK_H
#define CHOPSTICK_H

#include <mutex>
#include <string>

/**
 * Chopstick class
 * Represents a chopstick that philosophers use to eat
 * Each chopstick can only be used by one philosopher at a time
 */
class Chopstick {
private:
    std::string id_str; // String identifier for the chopstick
    int id_num;         // Numeric identifier for the chopstick (0-4)

public:
    std::mutex mtx;      // Mutex to control access to the chopstick

    // Default constructor
    Chopstick();

    // Constructor with string id
    Chopstick(std::string id_str);

    // Constructor with string id and numeric id
    Chopstick(std::string id_str, int id_num);

    // Get the chopstick's string id
    std::string getIdStr() const;

    // Get the chopstick's numeric id
    int getIdNum() const;

    // Set the chopstick's numeric id
    void setIdNum(int id);
};

#endif // CHOPSTICK_H