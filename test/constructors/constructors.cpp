#include <climits>
#include <random>

#define BIG_INT_TEST
#include "constructors/constructors.hpp"
#undef BIG_INT_TEST

#include "third_party/catch.hpp"


TEST_CASE("Construct zero-valued BigInts", "[constructors]") {
    BigInt num1;        // should be 0 by default
    REQUIRE(num1.magnitude.empty());
    REQUIRE(!num1.is_negative);

    BigInt num3(0l);     // 0 passed as an signed long
    REQUIRE(num3.magnitude.empty());
    REQUIRE(!num3.is_negative);

    BigInt num4("0");   // 0 passed as a decimal string
    REQUIRE(num4.magnitude.empty());
    REQUIRE(!num4.is_negative);

    BigInt num5(num4);  // object with value 0 passed to copy constructor
    REQUIRE(num5.magnitude.empty());
    REQUIRE(!num5.is_negative);

    BigInt num6(std::move(num4));  // object with value 0 passed to move constructor
    REQUIRE(num6.magnitude.empty());
    REQUIRE(!num6.is_negative);
}

TEST_CASE("Construct BigInts from decimal strings", "[constructors]") {
    // single char number
    BigInt num1("2");
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 2);
    REQUIRE(!num1.is_negative);

    // single char negative number
    BigInt num2("-7");
    REQUIRE(num2.magnitude.size() == 1);
    REQUIRE(num2.magnitude.front() == 7);
    REQUIRE(num2.is_negative);

    // 64 bit number
    BigInt num3("7523945");
    REQUIRE(num3.magnitude.size() == 1);
    REQUIRE(num3.magnitude.front() == 7523945);
    REQUIRE(!num3.is_negative);

    // negative 64 bit number
    BigInt num4("-5461283");
    REQUIRE(num4.magnitude.size() == 1);
    REQUIRE(num4.magnitude.front() == 5461283);
    REQUIRE(num4.is_negative);


    // 2^66 bit number
    BigInt num5("73786976294838206464");
    REQUIRE(num5.magnitude.size() == 2);
    REQUIRE(num5.magnitude[0] == 0);
    REQUIRE(num5.magnitude[1] == 4);
    REQUIRE(!num5.is_negative);

    // 12 * 2^128 + 437 * 2^64 + 998
    BigInt num6("4083388403051261569621722449392292594662");
    REQUIRE(num6.magnitude.size() == 3);
    REQUIRE(num6.magnitude[0] == 998);
    REQUIRE(num6.magnitude[1] == 437);
    REQUIRE(num6.magnitude[2] == 12);
    REQUIRE(!num6.is_negative);

    // 2^129 - 1
    BigInt num7("680564733841876926926749214863536422911");
    REQUIRE(num7.magnitude.size() == 3);
    REQUIRE(num7.magnitude[0] == 0xffffffffffffffff);
    REQUIRE(num7.magnitude[1] == 0xffffffffffffffff);
    REQUIRE(num7.magnitude[2] == 1);
    REQUIRE(!num7.is_negative);
}

TEST_CASE("Construct BigInts from hex strings", "[constructors]") {
    // single char number
    BigInt num1("0x2");
    REQUIRE(num1.magnitude.size() == 1);
    REQUIRE(num1.magnitude.front() == 2);
    REQUIRE(!num1.is_negative);

    // single char hex number
    BigInt num2("0xb");
    REQUIRE(num2.magnitude.size() == 1);
    REQUIRE(num2.magnitude.front() == 11);
    REQUIRE(!num2.is_negative);

    // single char number negative
    BigInt num3("-0x5");
    REQUIRE(num3.magnitude.size() == 1);
    REQUIRE(num3.magnitude.front() == 5);
    REQUIRE(num3.is_negative);

    // single char hex number negative
    BigInt num4("-0xd");
    REQUIRE(num4.magnitude.size() == 1);
    REQUIRE(num4.magnitude.front() == 13);
    REQUIRE(num4.is_negative);

    // simple hex
    BigInt num5("0x12ff8a6c");
    REQUIRE(num5.magnitude.size() == 1);
    REQUIRE(num5.magnitude.front() == 0x12ff8a6c);
    REQUIRE(!num5.is_negative);

    // simple hex negative
    BigInt num6("-0x4f8e99cac");
    REQUIRE(num6.magnitude.size() == 1);
    REQUIRE(num6.magnitude.front() == 0x4f8e99cac);
    REQUIRE(num6.is_negative);

    // simple upper hex
    BigInt num7("0x54F3EDC997A");
    REQUIRE(num7.magnitude.size() == 1);
    REQUIRE(num7.magnitude.front() == 0x54f3edc997a);
    REQUIRE(!num7.is_negative);

    // 128-bit hex
    BigInt num8("0xffff1111eeee2222dddd3333cccc4444");
    REQUIRE(num8.magnitude.size() == 2);
    REQUIRE(num8.magnitude[0] == 0xdddd3333cccc4444);
    REQUIRE(num8.magnitude[1] == 0xffff1111eeee2222);
    REQUIRE(!num8.is_negative);

    // 128-bit hex 0
    BigInt num9("-0x00000000000000000000000000000000");
    REQUIRE(num9.magnitude.size() == 0);
    REQUIRE(!num9.is_negative);

    // - 2^128
    BigInt num10("-0x100000000000000000000000000000000");
    REQUIRE(num10.magnitude.size() == 3);
    REQUIRE(num10.magnitude[0] == 0);
    REQUIRE(num10.magnitude[1] == 0);
    REQUIRE(num10.magnitude[2] == 1);
    REQUIRE(num10.is_negative);

}


TEST_CASE("Construct BigInts illegal decimal strings", "[constructors]") {
    // char at end
    try {
        BigInt num ("12345r");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'12345r\'"));
    }

    // char at begin
    try {
        BigInt num ("j12345");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'j12345\'"));
    }

    // char at middle
    try {
        BigInt num ("123t567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'123t567\'"));
    }

    // leading whitespace
    try {
        BigInt num (" 123567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \' 123567\'"));
    }

    // trailing whitespace
    try {
        BigInt num ("123567 ");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'123567 \'"));
    }

    // inner whitespace
    try {
        BigInt num ("123 567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'123 567\'"));
    }

    // leading period
    try {
        BigInt num (".123567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'.123567\'"));
    }

    // trailing period
    try {
        BigInt num ("123567.");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'123567.\'"));
    }

    // hex like
    try {
        BigInt num ("af123ff");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'af123ff\'"));
    }

    // double sign
    try {
        BigInt num ("--123567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'--123567\'"));
    }

    // double sign 2
    try {
        BigInt num ("++123567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'++123567\'"));
    }
}


TEST_CASE("Construct BigInts illegal hex strings", "[constructors]") {
    // char at end
    try {
        BigInt num ("0xffe12345r");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xffe12345r\'"));
    }

    // char at begin
    try {
        BigInt num ("0xzfa892");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xzfa892\'"));
    }

    // char at middle
    try {
        BigInt num ("0xce896k902");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xce896k902\'"));
    }

    // leading whitespace
    try {
        BigInt num ("0x ff33");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0x ff33\'"));
    }

    // trailing whitespace
    try {
        BigInt num ("0xffaa ");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xffaa \'"));
    }

    // inner whitespace
    try {
        BigInt num ("0xff aa");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xff aa\'"));
    }

    // leading period
    try {
        BigInt num ("0x.a1");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0x.a1\'"));
    }

    // trailing period
    try {
        BigInt num ("0xa2.");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0xa2.\'"));
    }

    // double sign
    try {
        BigInt num ("-0x-ff33");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'-0x-ff33\'"));
    }

    // sign after 0x
    try {
        BigInt num ("0x+123567");
        CHECK(false);
    }
    catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("Expected a hexadecimal integer, got \'0x+123567\'"));
    }
}
/*
TEST_CASE("Randomly construct BigInts from integers and strings",
          "[constructors][random][integer][string]") {
    std::random_device generator;
    // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution((LLONG_MIN), (LLONG_MAX));
    for (size_t i = 0; i < 30; i++) {
        long long rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num) == rand_num);
        REQUIRE(BigInt(std::to_string(rand_num)) == rand_num);
    }

    // should throw exception when invalid arguments are passed:
    try {
        BigInt trouble("123BigInt");    // without sign
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected an integer, got \'123BigInt\'"));
    }
    try {
        BigInt trouble("-4a5b6c");      // with sign
                                        // looks like hex, but is still not allowed
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected an integer, got \'-4a5b6c\'"));
    }
}
*/