#include "utils.h"

char* CreateCharPointerFromString(const std::string& str) {
    // Allocate memory for a new char array (including space for null terminator)
    char* new_char_ptr = new char[str.length() + 1];

    // Copy the contents of the std::string into the new char array
    std::strcpy(new_char_ptr, str.c_str());

    return new_char_ptr; // Return the new char pointer
}