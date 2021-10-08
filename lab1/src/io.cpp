#include "io.h"

void read_char_char_mapping(EncodedString* es, std::istream& istream, bool hints) {
    es->encoding_settings.pairs_char_char =
        new EncodedString::EncodingSettings::PairCharChar[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_char;
    hints&& std::cerr << "Total " << alphabet_length << " chars need to be shuffled\n";
    hints&& std::cerr << "Input mapping: |" << alphabet << "|\n";
    hints&& std::cerr << "             :  ";
    char buffer[500];
    istream >> buffer;
    if (strlen(buffer) != alphabet_length)
        throw std::runtime_error("not valid");
    // будем считать, что дублирующиеся преобразования не баг, а фича))

    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = buffer[i];
    }
}

void read_char_int32_mapping(EncodedString* es, std::istream& istream, bool hints) {
    es->encoding_settings.pairs_char_int32 =
        new EncodedString::EncodingSettings::PairCharInt32[alphabet_length];
    auto pairs = es->encoding_settings.pairs_char_int32;

    hints&& std::cerr << "Total " << alphabet_length << " chars need to be enumberated\n";
    hints&& std::cerr << "Input each after each: ";

    for (uint8_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        istream >> pairs[i].to;
    }
}

void read_encoding(EncodedString* es, std::istream& istream, bool hints) {
    hints&& std::cerr
        << "Specify encoding:\n1. Replace chars by chars\n2. Cyclic shift\n3. Replace chars "
           "by numbers\nInput: ";
    int32_t enc_id;
    istream >> enc_id;
    if (enc_id == 1) {
        es->encoding = Encoding::CharacterReplacing;
        es->encoded.chars = new char[strlen(es->str)];
        read_char_char_mapping(es, istream, hints);
    } else if (enc_id == 2) {
        es->encoding = Encoding::CyclicShift;
        es->encoded.chars = new char[strlen(es->str)];
        hints&& std::cerr << "Input shift factor: ";
        istream >> es->encoding_settings.shift_factor;
    } else if (enc_id == 3) {
        es->encoding = Encoding::CharacterReplacingByNumbers;
        es->encoded.ints = new int32_t[strlen(es->str)];
        read_char_int32_mapping(es, istream, hints);
    } else {
        throw std::runtime_error("unknown encoding");
    }
}

EncodedString** read(uint32_t* n, std::istream& istream, bool hints) {
    hints&& std::cerr << "Input amount of strings need to be encoded: ";
    istream >> *n;
    EncodedString** ess = new EncodedString*[*n];
    for (uint32_t i = 0; i < *n; ++i) {
        ess[i] = create_es();
        try {
            hints&& std::cerr << "Input string: ";
            istream >> ess[i]->str;
            read_encoding(ess[i], istream, hints);
        } catch (std::exception& e) {
            for (uint32_t j = 0; j < *n; ++j) {
                if (ess[j]) {
                    clear_es(ess[j]);
                    delete ess[j];
                }
            }
            delete[] ess;
            throw std::runtime_error(e.what());
        }
    }
    return ess;
}

EncodedString** read_from_file(uint32_t* n, char* input_filename) {
    std::fstream file;
    file.open(input_filename);
    EncodedString** ess = read(n, file, false);
    file.close();
    return ess;
}

EncodedString** read_from_stdin(uint32_t* n) {
    return read(n, std::cin, true);
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

void save_input(EncodedString** ess, uint32_t n, std::ostream& ostream) {
    ostream << "Total strings: " << n << '\n';
    ostream << "#,string,encoding,settings\n";
    for (uint32_t i = 0; i < n; ++i) {
        ostream << i << ',' << ess[i]->str << ',';
        if (ess[i]->encoding == Encoding::CharacterReplacing) {
            ostream << "Char-char" << ',';
            for (uint32_t j = 0; j < alphabet_length; ++j) {
                ostream << ess[i]->encoding_settings.pairs_char_char[j].to;
            }
        } else if (ess[i]->encoding == Encoding::CharacterReplacingByNumbers) {
            ostream << "Char-int32" << ',';
            for (uint32_t j = 0; j < alphabet_length; ++j) {
                ostream << ess[i]->encoding_settings.pairs_char_int32[j].to << ' ';
            }
        } else {
            ostream << "Shift" << ',';
            ostream << ess[i]->encoding_settings.shift_factor;
        }
        ostream << '\n';
    }
}

void save_output(EncodedString** ess, uint32_t n, std::ostream& ostream) {
    ostream << "\nSorted output:\n";
    ostream << "#,string,encoded\n";
    for (uint32_t i = 0; i < n; ++i) {
        ostream << i << ',' << ess[i]->str << ',';
        if (ess[i]->encoding == Encoding::CharacterReplacing ||
            ess[i]->encoding == Encoding::CyclicShift) {
            for (uint32_t j = 0; j < strlen(ess[i]->str); ++j) {
                ostream << ess[i]->encoded.chars[j];
            }
        } else {
            for (uint32_t j = 0; j < strlen(ess[i]->str); ++j) {
                ostream << ess[i]->encoded.ints[j] << ' ';
            }
        }
        ostream << '\n';
    }
}