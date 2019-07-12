#include <climits>
#include <random>

#define BIG_INT_TEST
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#undef BIG_INT_TEST

#include "third_party/catch.hpp"

TEST_CASE("implicit copy signed literal", "[assignment][operators]") {
    // simple pos
    BigInt num1 = 7523945;
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 7523945);
    REQUIRE(!num1.is_negative);

    // simple neg
    BigInt num2 = -7523945;
    REQUIRE(num2.magnitude.size() == 1);
    REQUIRE(num2.magnitude.front() == 7523945);
    REQUIRE(num2.is_negative);

    // max 63 bit
    BigInt num3 = 0x7fffffffffffffff;
    REQUIRE(num3.magnitude.size() == 1);
    REQUIRE(num3.magnitude.front() == 0x7fffffffffffffffl);
    REQUIRE(!num3.is_negative);

    // min 63 bit
    BigInt num4 = -0x8000000000000000;
    REQUIRE(num4.magnitude.size() == 1);
    REQUIRE(num4.magnitude.front() == 0x8000000000000000);
    REQUIRE(num4.is_negative);

    // 0
    BigInt num5 = 0l;
    REQUIRE(num5.magnitude.size() == 0);
    REQUIRE(!num5.is_negative);

    // - 0
    BigInt num6 = -0l;
    REQUIRE(num6.magnitude.size() == 0);
    REQUIRE(!num6.is_negative);
}

TEST_CASE("implicit copy string", "[assignment][operators]") {
    // pos string
    BigInt num1 = std::string("7523945");
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 7523945);
    REQUIRE(!num1.is_negative);

    // neg string
    BigInt num2 = std::string("-5461283");
    REQUIRE(num2.magnitude.size() == 1);
    REQUIRE(num2.magnitude.front() == 5461283);
    REQUIRE(num2.is_negative);

    // 12 * 2^128 + 437 * 2^64 + 998
    BigInt num3 = std::string("4083388403051261569621722449392292594662");
    REQUIRE(num3.magnitude.size() == 3);
    REQUIRE(num3.magnitude[0] == 998);
    REQUIRE(num3.magnitude[1] == 437);
    REQUIRE(num3.magnitude[2] == 12);
    REQUIRE(!num3.is_negative);

    // - (12 * 2^128 + 437 * 2^64 + 998)
    BigInt num4 = std::string("-4083388403051261569621722449392292594662");
    REQUIRE(num4.magnitude.size() == 3);
    REQUIRE(num4.magnitude[0] == 998);
    REQUIRE(num4.magnitude[1] == 437);
    REQUIRE(num4.magnitude[2] == 12);
    REQUIRE(num4.is_negative);
}

TEST_CASE("implicit copy c-style string literal", "[assignment][operators]") {
    // pos string
    BigInt num1 = "7523945";
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 7523945);
    REQUIRE(!num1.is_negative);

    // neg string
    BigInt num2 = "-5461283";
    REQUIRE(num2.magnitude.size() == 1);
    REQUIRE(num2.magnitude.front() == 5461283);
    REQUIRE(num2.is_negative);

    // 12 * 2^128 + 437 * 2^64 + 998
    BigInt num3 = "4083388403051261569621722449392292594662";
    REQUIRE(num3.magnitude.size() == 3);
    REQUIRE(num3.magnitude[0] == 998);
    REQUIRE(num3.magnitude[1] == 437);
    REQUIRE(num3.magnitude[2] == 12);
    REQUIRE(!num3.is_negative);

    // - (12 * 2^128 + 437 * 2^64 + 998)
    BigInt num4 = "-4083388403051261569621722449392292594662";
    REQUIRE(num4.magnitude.size() == 3);
    REQUIRE(num4.magnitude[0] == 998);
    REQUIRE(num4.magnitude[1] == 437);
    REQUIRE(num4.magnitude[2] == 12);
    REQUIRE(num4.is_negative);
}


TEST_CASE("explicit copy assignment", "[assignment][operators]") {
    // pos string
    BigInt num1 (7523945);
    BigInt cop1 = num1;
    // check num was not changed
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 7523945);
    REQUIRE(!num1.is_negative);
    // check cop
    REQUIRE(cop1.magnitude.size() == 1);
    REQUIRE(cop1.magnitude.front() == 7523945);
    REQUIRE(!cop1.is_negative);

    // 12 * 2^128 + 437 * 2^64 + 998
    BigInt num2 = "4083388403051261569621722449392292594662";
    BigInt cop2 = num2;
    // check num was not changed
    REQUIRE(num2.magnitude.size() == 3);
    REQUIRE(num2.magnitude[0] == 998);
    REQUIRE(num2.magnitude[1] == 437);
    REQUIRE(num2.magnitude[2] == 12);
    REQUIRE(!num2.is_negative);
    // check cop
    REQUIRE(cop2.magnitude.size() == 3);
    REQUIRE(cop2.magnitude[0] == 998);
    REQUIRE(cop2.magnitude[1] == 437);
    REQUIRE(cop2.magnitude[2] == 12);
    REQUIRE(!cop2.is_negative);

    // - (12 * 2^128 + 437 * 2^64 + 998)
    BigInt num3 = "-4083388403051261569621722449392292594662";
    BigInt cop3 = num3;
    // check num was not changed
    REQUIRE(num3.magnitude.size() == 3);
    REQUIRE(num3.magnitude[0] == 998);
    REQUIRE(num3.magnitude[1] == 437);
    REQUIRE(num3.magnitude[2] == 12);
    REQUIRE(num3.is_negative);
    // check cop
    REQUIRE(cop3.magnitude.size() == 3);
    REQUIRE(cop3.magnitude[0] == 998);
    REQUIRE(cop3.magnitude[1] == 437);
    REQUIRE(cop3.magnitude[2] == 12);
    REQUIRE(cop3.is_negative);
}


TEST_CASE("explicit move assignment", "[assignment][operators]") {
    // pos string
    BigInt num1 (7523945);
    BigInt mov1 = std::move(num1);
    // check num is now empty
    REQUIRE(num1.magnitude.empty());
    REQUIRE(!num1.is_negative);
    // check cop
    REQUIRE(mov1.magnitude.size() == 1);
    REQUIRE(mov1.magnitude.front() == 7523945);
    REQUIRE(!mov1.is_negative);

    // 12 * 2^128 + 437 * 2^64 + 998
    BigInt num2 = "4083388403051261569621722449392292594662";
    BigInt mov2 = std::move(num2);
    // check num is now empty
    REQUIRE(num2.magnitude.empty());
    REQUIRE(!num2.is_negative);
    // check cop
    REQUIRE(mov2.magnitude.size() == 3);
    REQUIRE(mov2.magnitude[0] == 998);
    REQUIRE(mov2.magnitude[1] == 437);
    REQUIRE(mov2.magnitude[2] == 12);
    REQUIRE(!mov2.is_negative);

    // - (12 * 2^128 + 437 * 2^64 + 998)
    BigInt num3 = "-4083388403051261569621722449392292594662";
    BigInt mov3 = std::move(num3);
    // check num is now empty
    REQUIRE(num3.magnitude.empty());
    REQUIRE(!num3.is_negative);
    // check cop
    REQUIRE(mov3.magnitude.size() == 3);
    REQUIRE(mov3.magnitude[0] == 998);
    REQUIRE(mov3.magnitude[1] == 437);
    REQUIRE(mov3.magnitude[2] == 12);
    REQUIRE(mov3.is_negative);
}