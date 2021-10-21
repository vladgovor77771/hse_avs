#include <chrono>
#include <iomanip>

#include "encoded_string/cc_string.h"
#include "encoded_string/ci_string.h"
#include "encoded_string/cs_string.h"
#include "io.h"
#include "sort.h"

char* create_random_string(uint32_t length) {
    char* res = new char[500];
    for (uint32_t i = 0; i < length; ++i) {
        res[i] = alphabet[std::rand() % alphabet_length];
    }
    res[length] = '\0';
    return res;
}

int32_t* create_random_int_array(uint32_t length) {
    int32_t* res = new int32_t[length];
    for (uint32_t i = 0; i < length; ++i) {
        res[i] = std::rand() % alphabet_length;
    }
    return res;
}

void benchmark_encode_char_char(uint32_t str_length) {
    char* mapping = create_random_string(alphabet_length);
    CCEncodedString* es = new CCEncodedString(create_random_string(50), mapping);

    auto t1 = std::chrono::high_resolution_clock::now();
    es->encode();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Char-char encoding of string with length " << std::setw(3) << str_length << ": "
              << std::setw(6) << diff.count() << " nanoseconds \n";

    delete es;
}

void benchmark_encode_char_int32(uint32_t str_length) {
    int32_t* mapping = create_random_int_array(alphabet_length);
    CIEncodedString* es = new CIEncodedString(create_random_string(str_length), mapping);

    auto t1 = std::chrono::high_resolution_clock::now();
    es->encode();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Char-int32 encoding of string with length " << std::setw(3) << str_length << ": "
              << std::setw(6) << diff.count() << " nanoseconds \n";

    delete es;
}

void benchmark_encode_shift(uint32_t str_length) {
    CSEncodedString* es =
        new CSEncodedString(create_random_string(str_length), std::rand() % alphabet_length);
    auto t1 = std::chrono::high_resolution_clock::now();
    es->encode();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Cyclic shift encoding of string with length " << std::setw(3) << str_length
              << ": " << std::setw(6) << diff.count() << " nanoseconds \n";

    delete es;
}

void benchmark_sort(uint32_t n) {
    BaseEncodedString** ess = new BaseEncodedString*[n];
    for (uint32_t i = 0; i < n; ++i) {
        char* mapping = create_random_string(alphabet_length);
        ess[i] = new CCEncodedString(create_random_string(50), mapping);
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    sort_array_of_encoded_strings_desc(ess, n);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Sort of " << std::setw(7) << n << " string: " << std::setw(13) << diff.count()
              << " nanoseconds \n";

    for (uint32_t i = 0; i < n; ++i) {
        delete ess[i];
    }
    delete[] ess;
}

int main() {
    std::cin.tie(NULL);

    benchmark_sort(50);
    benchmark_sort(100);
    benchmark_sort(500);
    benchmark_sort(1000);
    benchmark_sort(5000);
    benchmark_sort(10000);
    benchmark_sort(50000);

    benchmark_encode_char_char(50);
    benchmark_encode_char_char(100);
    benchmark_encode_char_char(200);
    benchmark_encode_char_char(300);
    benchmark_encode_char_char(400);
    benchmark_encode_char_char(499);

    benchmark_encode_char_int32(50);
    benchmark_encode_char_int32(100);
    benchmark_encode_char_int32(200);
    benchmark_encode_char_int32(300);
    benchmark_encode_char_int32(400);
    benchmark_encode_char_int32(499);

    benchmark_encode_shift(50);
    benchmark_encode_shift(100);
    benchmark_encode_shift(200);
    benchmark_encode_shift(300);
    benchmark_encode_shift(400);
    benchmark_encode_shift(499);

    return 0;
}