/*
    ===========================================================================
    Utility for parsing strings
    ===========================================================================
*/

#ifndef BIG_INT_PARSE_UTILITY_HPP
#define BIG_INT_PARSE_UTILITY_HPP

#include "addition.hpp"
#include "multiplication.hpp"


/*
    Parse a decimal string to a magnitude
    ----------------
*/

void parse_dec_magnitude (const std::string& string, std::vector<uint64_t>& magnitude, size_t start_index = 0) {
    for (size_t index = start_index; index < string.size(); index++) {
        unsigned char c = string[index];
        if (c >= '0' and c <= '9') {
            multiply_unsigned_to_magnitude(magnitude, 10);
            add_unsigned_to_magnitude(magnitude, c - '0');
        }
        else {
            throw std::invalid_argument("Expected a decimal integer, got \'" + string + "\'");
        }
    }
}

/*
    Parse a hex string to a magnitude
    ----------------
*/

void parse_hex_magnitude (const std::string& string, std::vector<uint64_t>& magnitude, size_t start_index = 0) {
    // check that every char is valid
    for (auto c = string.begin() + start_index; c != string.end(); c ++) {
        if (!std::isxdigit(*c))
            throw std::invalid_argument("Expected a hexadecimal integer, got \'" + string + "\'");
    }
    size_t unpushed = 0;
    // move in 16 hex chars blocks -> 64 bit numbers
    for (size_t index = string.size(); index >= start_index+16; index-=16) {
        auto str = string.substr(index-16, 16);
        uint64_t value = std::strtoull(str.c_str(), nullptr,16);
        if (value) {
            // add zeros lazily
            magnitude.resize(magnitude.size() + unpushed, 0);
            magnitude.push_back(value);
            unpushed = 0;
        }
        else
            unpushed++;
    }
    // start block handled in loop
    if (start_index % 16 == string.size() % 16)
        return;
    // length of start block
    size_t len = (string.size() + 16 - start_index) % 16;
    auto str = string.substr(start_index, len);
    uint64_t value = std::strtoull(str.c_str(), nullptr, 16);

    if (value) {
        // add zeros lazily
        magnitude.resize(magnitude.size() + unpushed, 0);
        magnitude.push_back(value);
    }
}


/*
    Parse a string to a big int
    ----------------
*/

void parse_big_int(const std::string& num, std::vector<uint64_t>& magnitude, bool& is_negative) {
    size_t index = 0;
    if (num[index] == '-') {
        is_negative = true;
        index++;
    }
    else if (num[index] == '+') {
        index++;
    }

    if (num[index] == '0' and num[index+1] == 'x') {
        index += 2;
        parse_hex_magnitude(num, magnitude, index);
    }
    else if (num[index] == '0' and num[index+1] == 'b') {
        // TODO
        throw "Not implemented!";
    }
    else {
        parse_dec_magnitude(num, magnitude, index);
    }

    if(magnitude.empty()) {
        is_negative = false;
    }
}

#endif //BIG_INT_PARSE_UTILITY_HPP
