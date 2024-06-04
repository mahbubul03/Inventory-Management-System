#ifndef DATASERIALIZER_H
#define DATASERIALIZER_H
#include <sstream> // for std::ostringstream

// Base case for recursion, when there are no more arguments
void serializeDataHelper(std::ostringstream& oss) {}

// Recursive function to process each argument
template<typename T, typename... Args>
void serializeDataHelper(std::ostringstream& oss, const T& firstArg, const Args&... args) {
    oss << firstArg;  // Append the first argument to the stringstream
    serializeDataHelper(oss, args...);  // Recur for the remaining arguments
}

// Method to concatenate variables of different types into a string
template<typename... Args>
std::string serializeData(const Args&... args) {
    std::ostringstream oss;
    serializeDataHelper(oss, args...);  // Call the recursive helper function
    return oss.str();  // Return the concatenated string
}

#endif // DATASERIALIZER_H
