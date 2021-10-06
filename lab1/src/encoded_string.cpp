#include "encoded_string.h"

EncodedString *create_es() {
    EncodedString *es = new EncodedString;
    char *buffer = new char[500];
    es->str = buffer;
    return es;
}

void encode_character_replacing(EncodedString *es) {
    for (uint32_t i = 0; i < strlen(es->str); ++i) {
        for (uint32_t j = 0; j < alphabet_length; ++j) {
            if (es->str[i] == es->encoding_settings.pairs_char_char[j].from) {
                es->encoded.chars[i] = es->encoding_settings.pairs_char_char[j].to;
                break;
            }
        }
    }
}

void encode_cyclic_shift(EncodedString *es) {
    for (uint32_t i = 0; i < strlen(es->str); ++i) {
        for (int32_t j = 0; j < alphabet_length; ++j) {
            if (es->str[i] == alphabet[j]) {
                int32_t cur = (j + es->encoding_settings.shift_factor) % alphabet_length;
                if (cur < 0) {
                    cur += alphabet_length;
                }
                es->encoded.chars[i] = alphabet[cur];
                break;
            }
        }
    }
}

void encode_character_replacing_by_numbers(EncodedString *es) {
    for (uint32_t i = 0; i < strlen(es->str); ++i) {
        for (uint32_t j = 0; j < alphabet_length; ++j) {
            if (es->str[i] == es->encoding_settings.pairs_char_int32[j].from) {
                es->encoded.ints[i] = es->encoding_settings.pairs_char_int32[j].to;
                break;
            }
        }
    }
}

void encode(EncodedString *es) {
    if (es->encoding == Encoding::CharacterReplacing)
        encode_character_replacing(es);
    else if (es->encoding == Encoding::CyclicShift)
        encode_cyclic_shift(es);
    else if (es->encoding == Encoding::CharacterReplacingByNumbers)
        encode_character_replacing_by_numbers(es);
}

void clear_es(EncodedString *es) {
    delete[] es->str;
    if (es->encoding == Encoding::CharacterReplacing) {
        if (es->encoded.chars) {
            delete[] es->encoded.chars;
        }
        if (es->encoding_settings.pairs_char_char) {
            delete[] es->encoding_settings.pairs_char_char;
        }
    } else if (es->encoding == Encoding::CyclicShift) {
        if (es->encoded.chars) {
            delete[] es->encoded.chars;
        }
    } else if (es->encoding == Encoding::CharacterReplacingByNumbers) {
        if (es->encoded.ints) {
            delete[] es->encoded.ints;
        }
        if (es->encoding_settings.pairs_char_int32) {
            delete[] es->encoding_settings.pairs_char_int32;
        }
    }
}
