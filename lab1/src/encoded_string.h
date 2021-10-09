#ifndef ENCODED_STRING_H
#define ENCODED_STRING_H
#include <cstdint>
#include <cstring>
#include <iostream>

const int32_t alphabet_length = 62;
const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

enum Encoding { CharacterReplacing, CyclicShift, CharacterReplacingByNumbers };

struct EncodedString {
    char* str;  // decoded
    Encoding encoding;

    union EncodedVault {
        char* chars;
        int32_t* ints;
    } encoded;

    union EncodingSettings {
        int32_t shift_factor;
        struct PairCharChar {
            char from;
            char to;
        } * pairs_char_char;
        struct PairCharInt32 {
            char from;
            int32_t to;
        } * pairs_char_int32;
    } encoding_settings;
};

EncodedString* create_es();
void encode(EncodedString* es);
void clear_es(EncodedString* es);

#endif
