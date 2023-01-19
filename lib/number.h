#pragma once
#include <cinttypes>
#include <iostream>


struct uint2022_t {

    // uint_numbers contains the uint2022_t number in chunks
    // chunk contains 9 digits of uint2022_t number
    int uint_numbers[68];

    // actual_chunk refers to the first chunk which contains first numbers of uint2022_t if its divided using rules above
    size_t actual_chunk;

    static const int base = 1000000000;
    static const size_t chunks_reserved_amount = 68;
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
