/*
    ===========================================================================
    Utility for multiplication
    ===========================================================================
*/

#ifndef BIG_INT_MULTIPLICATION_UTILITY_HPP
#define BIG_INT_MULTIPLICATION_UTILITY_HPP

#include "addition.hpp"


/*
    Multiply 64 bit numbers a and b.
    Low 64 bits are returned.
    High 64 bits are stored in hi
    ----------------
*/

uint64_t mulx (uint64_t a, uint64_t b, uint64_t& hi) {
    // TODO : use mulx
    constexpr uint64_t lowmask = (1ul<<32u)-1;
    uint64_t a_low = a & lowmask;
    uint64_t a_high = a >> 32u;
    uint64_t b_low = b & lowmask;
    uint64_t b_high = b >> 32u;

    uint64_t low = static_cast<uint64_t>(a_low)*b_low;
    uint64_t med1 = a_high * b_low;
    uint64_t med2 = a_low * b_high;
    hi = a_high * b_high;

    bool carry;
    low = add_carry(low, med1 << 32u, carry);
    if (carry)
        ++hi;
    low = add_carry(low, med2 << 32u, carry);
    if (carry)
        ++hi;

    // cannot overflow
    hi += med1 >> 32u;
    hi += med2 >> 32u;

    return low;
}


/*
    Multiply unsigned to magnitude
    ----------------
*/

void multiply_unsigned_to_magnitude (std::vector<uint64_t>& magnitude, uint64_t value) {
    // empty magnitude stays empty
    if (magnitude.empty()) {
        return;
    }
    // clear magnitude
    if (value == 0) {
        magnitude.clear();
        return;
    }
    // do nothing (multiplication with 1)
    if (value == 1) {
        return;
    }
    // TODO : base 2 optimization
    // default case
    std::vector<uint64_t> mag_copy = magnitude;
    for (auto& ma : magnitude)
        ma = 0;
    uint64_t carry;
    for (size_t index = 0; index < mag_copy.size(); ++index) {
        uint64_t mul_res = mulx(mag_copy[index], value, carry);
        add_unsigned_to_magnitude(magnitude, mul_res, index);
        add_unsigned_to_magnitude(magnitude, carry, index+1);
    }
}

#endif //BIG_INT_MULTIPLICATION_UTILITY_HPP
