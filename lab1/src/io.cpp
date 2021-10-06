#include "io.h"

void read_str(char* buffer) {
    std::cerr << "Input string: ";
    std::cin >> buffer;
}

void read_char_char_mapping(EncodedString* es) {
    es->encoding_settings.pairs_char_char =
        new EncodedString::EncodingSettings::PairCharChar[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_char;
    std::cerr << "Total " << alphabet_length << " chars need to be shuffled\n";
    std::cerr << "Input mapping: |" << alphabet << "|\n";
    std::cerr << "             :  ";
    char buffer[500];
    std::cin >> buffer;
    if (strlen(buffer) != alphabet_length)
        throw std::runtime_error("not valid");
    // будем считать, что дублирующиеся преобразования не баг, а фича))

    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = buffer[i];
    }
}

void read_char_int32_mapping(EncodedString* es) {
    es->encoding_settings.pairs_char_int32 =
        new EncodedString::EncodingSettings::PairCharInt32[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_int32;

    std::cerr << "Total " << alphabet_length << " chars need to be enumberated\n";
    std::cerr << "Input each after each: ";

    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        std::cin >> pairs[i].to;
    }
}

void read_encoding(EncodedString* es) {
    std::cerr << "Specify encoding:\n1. Replace chars by chars\n2. Cyclic shift\n3. Replace chars "
                 "by numbers\nInput: ";
    int32_t enc_id;
    std::cin >> enc_id;
    if (enc_id == 1) {
        es->encoding = Encoding::CharacterReplacing;
        es->encoded.chars = new char[strlen(es->str)];
        read_char_char_mapping(es);
    } else if (enc_id == 2) {
        es->encoding = Encoding::CyclicShift;
        es->encoded.chars = new char[strlen(es->str)];
        std::cerr << "Input shift factor: ";
        std::cin >> es->encoding_settings.shift_factor;
    } else if (enc_id == 3) {
        es->encoding = Encoding::CharacterReplacingByNumbers;
        es->encoded.ints = new int32_t[strlen(es->str)];
        read_char_int32_mapping(es);
    } else {
        throw std::runtime_error("unknown encoding");
    }
}

void print_encoded(EncodedString* es) {
    std::cerr << "Encoded: ";
    if (es->encoding == Encoding::CharacterReplacing || es->encoding == Encoding::CyclicShift) {
        for (uint32_t i = 0; i < strlen(es->str); ++i) {
            std::cout << es->encoded.chars[i];
        }
    } else if (es->encoding == Encoding::CharacterReplacingByNumbers) {
        for (uint32_t i = 0; i < strlen(es->str); ++i) {
            std::cout << es->encoded.ints[i] << ' ';
        }
    }
    std::cout << '\n';
}

void print_str(EncodedString* es) {
    std::cerr << "Len: " << strlen(es->str) << " Str: ";
    for (uint32_t i = 0; i < strlen(es->str); ++i) {
        std::cerr << es->str[i];
    }
    std::cerr << "\n";
}