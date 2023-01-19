#include "number.h"
#include <iostream>

uint2022_t from_uint(uint32_t i) {

    uint2022_t new_uint2022_t;

    // buff contains uint32_t as a string
    std::string buff;
    buff = std::to_string(i);

    // size_of_buff means size of uint32_t number
    int size_of_buff = 0;

    // string_of_digits is used to contain chunk as a string to later convert into int
    std::string string_of_digits;

    // add_size is used to easier define the amount of needed chunks for a specific number
    int add_size = 1;

    while(buff[size_of_buff] != '\0') size_of_buff++;

    if (size_of_buff % 9 == 0) {
        add_size = 0;
    }

    if (size_of_buff / 9 > 0) {
        new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - (size_of_buff / 9) - add_size;
    } else {
        new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - 1;
    }

    size_t massive_actual_index = new_uint2022_t.actual_chunk;

    // implementation of transfer number in chunks
    if (size_of_buff % 9 == 0 && (size_of_buff / 9) > 0) {
        for (size_t r = 0; r < size_of_buff; r += 9){
            for (size_t j = 0; j < 9; j++) {
                string_of_digits += buff[r + j];
            }
            new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
            string_of_digits.clear();
            massive_actual_index++;
        }
    } else if (size_of_buff % 9 != 0 && (size_of_buff / 9) > 0) {
        for (size_t r = 0; r < size_of_buff % 9; r++) {
            string_of_digits += buff[r];
        }
        new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
        string_of_digits.clear();
        massive_actual_index++;
        for (size_t r = (size_of_buff % 9); r < size_of_buff; r += 9) {
            for (size_t j = 0; j < 9; j++) {
                string_of_digits += buff[r+j];
            }
            new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
            // .clear() makes the string empty
            string_of_digits.clear();
            massive_actual_index++;
        }
    } else if (size_of_buff % 9 != 0 && (size_of_buff / 9) == 0) {
        for (size_t r = 0; r < size_of_buff; r++) {
            string_of_digits += buff[r];
        }
        new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
        string_of_digits.clear();
    }

    return new_uint2022_t;
}

uint2022_t from_string(const char* buff) {

    uint2022_t new_uint2022_t;
    size_t size_of_buff = 0;
    std::string string_of_digits;
    int add_size = 1;

    while(buff[size_of_buff] != '\0') size_of_buff++;

    if (size_of_buff % 9 == 0) {
        add_size = 0;
    }

    if (size_of_buff / 9 > 0) {
        new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - (size_of_buff / 9) - add_size;
    } else {
        new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - 1;
    }

    size_t massive_actual_index = new_uint2022_t.actual_chunk;

    if (size_of_buff % 9 == 0 && (size_of_buff / 9) > 0) {
        for (size_t i = 0; i < size_of_buff; i += 9){
            for (size_t j = 0; j < 9; j++) {
                string_of_digits += buff[i+j];
            }
            new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
            string_of_digits.clear();
            massive_actual_index++;
        }
    } else if (size_of_buff % 9 != 0 && (size_of_buff / 9) > 0) {
        for (size_t i = 0; i < size_of_buff % 9; i++) {
            string_of_digits += buff[i];
        }
        new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
        string_of_digits.clear();
        massive_actual_index++;
        for (size_t i = (size_of_buff % 9); i < size_of_buff; i+=9) {
            for (size_t j = 0; j < 9; j++) {
                string_of_digits += buff[i + j];
            }
            new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
            string_of_digits.clear();
            massive_actual_index++;
        }
    } else if (size_of_buff % 9 != 0 && (size_of_buff / 9) == 0) {
        for (size_t i = 0; i < size_of_buff; i++) {
            string_of_digits += buff[i];
        }
        new_uint2022_t.uint_numbers[massive_actual_index] = stoi(string_of_digits);
        string_of_digits.clear();
    }

    return new_uint2022_t;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t new_uint2022_t;

    // current_add and next_add are used as helpful variables in future calculations
    int current_add = 0;
    int next_add = 0;
    size_t max_length = std::min(lhs.actual_chunk, rhs.actual_chunk);
    size_t min_length = std::max(lhs.actual_chunk, rhs.actual_chunk);
    // sets chunk amount for new uint2022_t number
    new_uint2022_t.actual_chunk = max_length;

    for (size_t i = uint2022_t::chunks_reserved_amount - 1; i >= min_length; i--) {
        current_add = (lhs.uint_numbers[i] + rhs.uint_numbers[i] + next_add) % uint2022_t::base;
        new_uint2022_t.uint_numbers[i] = current_add;
        next_add = (lhs.uint_numbers[i] + rhs.uint_numbers[i] + next_add) / uint2022_t::base;
    }

    // to easier calculate when there are no more digits in one of numbers
    if (lhs.actual_chunk < rhs.actual_chunk) {
        for (size_t i = min_length - 1; i >= max_length; i--) {
            current_add = (lhs.uint_numbers[i] + next_add) % uint2022_t::base;
            new_uint2022_t.uint_numbers[i] = current_add;
            next_add = (lhs.uint_numbers[i] + next_add) / uint2022_t::base;
        }
    } else if (rhs.actual_chunk < lhs.actual_chunk) {
        for (size_t i = min_length - 1; i >= max_length; i--) {
            current_add = (rhs.uint_numbers[i] + next_add) % uint2022_t::base;
            new_uint2022_t.uint_numbers[i] = current_add;
            next_add = (rhs.uint_numbers[i] + next_add) / uint2022_t::base;
        }
    }

    // if we pass through a digit of a number it adds 1
    if (next_add == 1) {
        new_uint2022_t.uint_numbers[max_length - 1] = 1;
        new_uint2022_t.actual_chunk -= 1;
    }

    return new_uint2022_t;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t new_uint2022_t;
    int current_del = 0;
    int next_del = 0;
    size_t max_length = std::min(lhs.actual_chunk, rhs.actual_chunk);
    size_t min_length = std::max(lhs.actual_chunk, rhs.actual_chunk);
    new_uint2022_t.actual_chunk = max_length;

    for (size_t i = uint2022_t::chunks_reserved_amount - 1; i >= min_length; i--) {
        current_del = (lhs.uint_numbers[i] - rhs.uint_numbers[i] + next_del);
        if (current_del < 0) {
            current_del += uint2022_t::base;
            next_del = -1;
        } else {
            next_del = 0;
        }
        new_uint2022_t.uint_numbers[i] = current_del;
    }

    // according to the task lhs is always greater than rhs
    if (lhs.actual_chunk < rhs.actual_chunk) {
        for (size_t i = min_length - 1; i >= max_length; i--) {
            current_del = (lhs.uint_numbers[i] + next_del);
            if (current_del < 0) {
                current_del += uint2022_t::base;
                next_del = -1;
            } else {
                next_del = 0;
            }
            new_uint2022_t.uint_numbers[i] = current_del;
        }
    }

    return new_uint2022_t;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t new_uint2022_t;
    size_t size_of_massive = (uint2022_t::chunks_reserved_amount * 2) - (lhs.actual_chunk + rhs.actual_chunk);
    new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - size_of_massive;
    // sums of indexes of 2 multiplied numbers helps us divide resulting sums into numbers that would obtain as in lines (considering a shift of line)
    int massive_of_sums[size_of_massive] = {};
    // protects from overflow in massive_of_sums elements
    int help_operator = 0;
    int current_mult = 0;
    int next_mult = 0;
    bool flag = false;

    for (size_t i = uint2022_t::chunks_reserved_amount - 1; i >= rhs.actual_chunk; i--) {
        for (size_t j = uint2022_t::chunks_reserved_amount - 1; j >= lhs.actual_chunk; j--) {
            help_operator = massive_of_sums[134 - i - j];
            massive_of_sums[134 - i - j] %= uint2022_t::base;
            massive_of_sums[134 - i - j + 1] += help_operator / uint2022_t::base;
            massive_of_sums[134 - i - j] += ((unsigned long long) rhs.uint_numbers[i] * (unsigned long long) lhs.uint_numbers[j]) % uint2022_t::base;
            massive_of_sums[134 - i - j + 1] += ((unsigned long long) rhs.uint_numbers[i] * (unsigned long long) lhs.uint_numbers[j]) / uint2022_t::base;
        }
    }

    for (size_t i = 0; i <= size_of_massive; i++) {
        current_mult = massive_of_sums[i] + next_mult;
        new_uint2022_t.uint_numbers[(uint2022_t::chunks_reserved_amount - 1) - i] = current_mult % uint2022_t::base;
        next_mult = current_mult / uint2022_t::base;
    }

    // deletes starting zeros
    if (new_uint2022_t.uint_numbers[new_uint2022_t.actual_chunk] == 0) {
        flag = false;
        for (size_t i = new_uint2022_t.actual_chunk; i < uint2022_t::chunks_reserved_amount; i++) {
            if (new_uint2022_t.uint_numbers[i] != 0) {
                new_uint2022_t.actual_chunk = i;
                flag = true;
                break;
            }
        }
        if (!flag) {
            new_uint2022_t.actual_chunk = uint2022_t::chunks_reserved_amount - 1;
        }
    }

    return new_uint2022_t;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {

    bool result = false;

    if (lhs.actual_chunk == rhs.actual_chunk) {
        result = true;
        for (size_t i = lhs.actual_chunk; i < uint2022_t::chunks_reserved_amount; i++) {
            if (lhs.uint_numbers[i] != rhs.uint_numbers[i]) {
                result = false;
                break;
            }
        }
    }

    return result;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {

    bool result = true;

    if (lhs == rhs) {
        result = false;
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {

    // handles all options in case we have some zeros at the beginning
    int element_length = 0;
    int massive_element = 0;
    size_t start_index = 0;
    for (size_t i = value.actual_chunk; i < uint2022_t::chunks_reserved_amount; i++) {
        if (value.uint_numbers[i] != 0) {
            start_index = i;
            break;
        }
    }
    if (start_index == 0) {
        stream << 0;
    } else {
        stream << value.uint_numbers[start_index];
        for (size_t i = start_index + 1; i < uint2022_t::chunks_reserved_amount; i++) {
            element_length = 0;
            massive_element = value.uint_numbers[i];
            if (massive_element == 0) {
                element_length = 1;
            } else {
                while (massive_element) {
                    element_length++;
                    massive_element /= 10;
                }
            }
            for (size_t k = 1; k <= 9 - element_length; k++) {
                stream << 0;
            }
            stream << value.uint_numbers[i];
        }
    }
    stream << "\n";
    return stream;
}
