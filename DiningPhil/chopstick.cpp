#include "chopstick.h"

/**
 * Default constructor for Chopstick
 */
Chopstick::Chopstick() {
    this->id_str = "Unnamed chopstick";
    this->id_num = -1; // Invalid ID
}

/**
 * Constructor for Chopstick with a string ID
 * @param id_str The string identifier for the chopstick
 */
Chopstick::Chopstick(std::string id_str) : id_str(id_str) {
    this->id_num = -1; // Invalid ID
}

/**
 * Constructor for Chopstick with string and numeric IDs
 * @param id_str The string identifier for the chopstick
 * @param id_num The numeric identifier for the chopstick
 */
Chopstick::Chopstick(std::string id_str, int id_num) : id_str(id_str), id_num(id_num) {
}

/**
 * Get the chopstick's string ID
 * @return The chopstick's string ID
 */
std::string Chopstick::getIdStr() const {
    return id_str;
}

/**
 * Get the chopstick's numeric ID
 * @return The chopstick's numeric ID
 */
int Chopstick::getIdNum() const {
    return id_num;
}

/**
 * Set the chopstick's numeric ID
 * @param id The numeric ID to set
 */
void Chopstick::setIdNum(int id) {
    id_num = id;
}