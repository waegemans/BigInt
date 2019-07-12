/*
    ===========================================================================
    Utility for addition
    ===========================================================================
*/

#ifndef BIG_INT_ADDITION_UTILITY_HPP
#define BIG_INT_ADDITION_UTILITY_HPP


/*
    Adds two 64-bit unsigned integers.
    stores if there is a carry.
    ----------------
*/

uint64_t add_carry (uint64_t a, uint64_t b, bool& carry) {
    // TODO : use adx
    carry = (std::numeric_limits<uint64_t>::max() - a < b);
    return a+b;
}


/*
    Add unsigned to magnitude
    ----------------
*/

void add_unsigned_to_magnitude (std::vector<uint64_t>& magnitude, uint64_t value, size_t start_index=0) {
    // do nothing
    if (value == 0)
        return;
    // fill missing idx with 0
    if (magnitude.size() < start_index) {
        magnitude.resize(start_index, 0);
    }
    // fill empty magnitude
    if (magnitude.size() == start_index) {
        magnitude.push_back(value);
        return;
    }
    // overflow
    if (std::numeric_limits<uint64_t>::max() - magnitude[start_index] < value) {
        magnitude[start_index] += value;
        // set carry bit
        bool carry = true;
        for (size_t index = 1; carry; ++index) {
            if (index == magnitude.size()) {
                magnitude.push_back(1);
                return;
            }
            carry = magnitude[index] == std::numeric_limits<uint64_t>::max();
            if (carry)
                magnitude[index] = 0;
            else
                magnitude[index]++;
        }
    }
    // no overflow
    else {
        magnitude[start_index] += value;
    }

}

#endif //BIG_INT_ADDITION_UTILITY_HPP
