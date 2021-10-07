#include <chrono>
#include <iomanip>

#include "encoded_string.h"
#include "io.h"
#include "sort.h"

void set_random_str(EncodedString* es, uint32_t length) {
    for (uint32_t i = 0; i < length; ++i) {
        es->str[i] = alphabet[std::rand() % alphabet_length];
    }
    es->str[length] = '\0';
}

void benchmark_encode_char_char(uint32_t str_length) {
    EncodedString* es = create_es();
    set_random_str(es, str_length);
    es->encoding = Encoding::CharacterReplacing;
    es->encoded.chars = new char[str_length];
    es->encoding_settings.pairs_char_char =
        new EncodedString::EncodingSettings::PairCharChar[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_char;
    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = alphabet[std::rand() % alphabet_length];
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    encode(es);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Char-char encoding of string with length " << std::setw(3) << str_length << ": "
              << std::setw(6) << diff.count() << " nanoseconds \n";

    clear_es(es);
    delete es;
}

void benchmark_encode_char_int32(uint32_t str_length) {
    EncodedString* es = create_es();
    set_random_str(es, str_length);
    es->encoding = Encoding::CharacterReplacingByNumbers;
    es->encoded.ints = new int32_t[str_length];
    es->encoding_settings.pairs_char_int32 =
        new EncodedString::EncodingSettings::PairCharInt32[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_int32;
    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = std::rand() % alphabet_length;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    encode(es);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Char-int32 encoding of string with length " << std::setw(3) << str_length << ": "
              << std::setw(6) << diff.count() << " nanoseconds \n";

    clear_es(es);
    delete es;
}

void benchmark_encode_shift(uint32_t str_length) {
    EncodedString* es = create_es();
    set_random_str(es, str_length);
    es->encoding = Encoding::CyclicShift;
    es->encoded.chars = new char[str_length];
    es->encoding_settings.shift_factor = std::rand() % alphabet_length;

    auto t1 = std::chrono::high_resolution_clock::now();
    encode(es);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Cyclic shift encoding of string with length " << std::setw(3) << str_length
              << ": " << std::setw(6) << diff.count() << " nanoseconds \n";

    clear_es(es);
    delete es;
}

void benchmark_sort(uint32_t n) {
    EncodedString** ess = new EncodedString*[n];
    for (uint32_t i = 0; i < n; ++i) {
        ess[i] = create_es();
        set_random_str(ess[i], 50);
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    sort_array_of_encoded_strings_desc(ess, n);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Sort of " << std::setw(7) << n << " string: " << std::setw(13) << diff.count()
              << " nanoseconds \n";

    for (uint32_t i = 0; i < n; ++i) {
        clear_es(ess[i]);
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