/*
    ===========================================================================
    Constructors
    ===========================================================================
*/

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

#include "BigInt.hpp"
#include "utility/parse.hpp"


/*
    Default constructor
    -------------------
*/

BigInt::BigInt() : magnitude {}, is_negative(false) {}


/*
    Copy constructor
    ----------------
*/

BigInt::BigInt(const BigInt& other) : magnitude(other.magnitude), is_negative(other.is_negative) {}


/*
    Move constructor
    ----------------
*/

BigInt::BigInt(BigInt&& other) noexcept : magnitude(std::move(other.magnitude)), is_negative(other.is_negative) {
    other.is_negative = false;
}


/*
    64 bit signed to BigInt
    -----------------
*/

BigInt::BigInt(const int64_t& num) : magnitude {}, is_negative(num < 0) {
    // only add non zero
    if (num)
        magnitude.emplace_back(std::abs(num));
}


/*
    String to BigInt
    ----------------
*/

BigInt::BigInt(const std::string& num) : magnitude{}, is_negative(false) {
    parse_big_int(num, magnitude, is_negative);
}


/*
    c-style String to BigInt
    ----------------
*/

BigInt::BigInt(const char* str) : magnitude{}, is_negative(false) {
    std::string num(str);
    parse_big_int(num, magnitude, is_negative);
}

#endif  // BIG_INT_CONSTRUCTORS_HPP
