/*
    ===========================================================================
    Assignment operators
    ===========================================================================
*/

#ifndef BIG_INT_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ASSIGNMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"


/*

    Copy assignment
    ---------------
*/

BigInt& BigInt::operator=(const BigInt& other) {
    magnitude = other.magnitude;
    is_negative = other.is_negative;

    return *this;
}


/*

    Move assignment
    ---------------
*/

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    magnitude = std::move(other.magnitude);
    is_negative = other.is_negative;

    other.is_negative = false;

    return *this;
}


#endif  // BIG_INT_ASSIGNMENT_OPERATORS_HPP
