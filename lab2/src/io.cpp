#include "io.h"

char* read_char_char_mapping(std::istream& istream, bool hints) {
    hints&& std::cerr << "Total " << alphabet_length << " chars need to be shuffled\n";
    hints&& std::cerr << "Input mapping: |" << alphabet << "|\n";
    hints&& std::cerr << "             :  ";
    char* buffer = new char[500];
    istream >> buffer;
    if (strlen(buffer) != alphabet_length) {
        delete[] buffer;
        throw std::runtime_error("not valid");
    }
    // будем считать, что дублирующиеся преобразования не баг, а фича))
    return buffer;
}

int32_t* read_char_int32_mapping(std::istream& istream, bool hints) {
    hints&& std::cerr << "Total " << alphabet_length << " chars need to be enumberated\n";
    hints&& std::cerr << "Input each after each: ";
    int32_t* res = new int32_t[alphabet_length];
    for (uint8_t i = 0; i < alphabet_length; ++i) {
        istream >> res[i];
    }
    return res;
}

Encoding read_encoding(std::istream& istream, bool hints) {
    hints&& std::cerr
        << "Specify encoding:\n1. Replace chars by chars\n2. Cyclic shift\n3. Replace chars "
           "by numbers\nInput: ";
    int32_t enc_id;
    istream >> enc_id;
    if (enc_id == 1) {
        return Encoding::CharacterReplacing;
    } else if (enc_id == 2) {
        return Encoding::CyclicShift;
    } else if (enc_id == 3) {
        return Encoding::CharacterReplacingByNumbers;
    } else {
        throw std::runtime_error("unknown encoding");
    }
}

BaseEncodedString** read(uint32_t* n, std::istream& istream, bool hints) {
    hints&& std::cerr << "Input amount of strings need to be encoded: ";
    istream >> *n;
    BaseEncodedString** ess = new BaseEncodedString*[*n];
    for (uint32_t i = 0; i < *n; ++i) {
        ess[i] = nullptr;
    }
    char* str = nullptr;
    for (uint32_t i = 0; i < *n; ++i) {
        try {
            hints&& std::cerr << "Input string: ";
            str = new char[500];
            istream >> str;
            Encoding enc = read_encoding(istream, hints);
            if (enc == Encoding::CharacterReplacing) {
                char* mapping = read_char_char_mapping(istream, hints);
                ess[i] = new CCEncodedString(str, mapping);
            } else if (enc == Encoding::CharacterReplacingByNumbers) {
                int32_t* mapping = read_char_int32_mapping(istream, hints);
                ess[i] = new CIEncodedString(str, mapping);
            } else if (enc == Encoding::CyclicShift) {
                int32_t sf;
                istream >> sf;
                ess[i] = new CSEncodedString(str, sf);
            }
            str = nullptr;
        } catch (std::exception& e) {
            if (str) {
                delete[] str;
            }
            for (uint32_t j = 0; j < *n; ++j) {
                if (ess[j]) {
                    delete ess[j];
                }
            }
            delete[] ess;
            throw std::runtime_error(e.what());
        }
    }
    return ess;
}

BaseEncodedString** read_from_file(uint32_t* n, char* input_filename) {
    std::fstream file;
    file.open(input_filename);
    BaseEncodedString** ess = read(n, file, false);
    file.close();
    return ess;
}

BaseEncodedString** read_from_stdin(uint32_t* n) {
    return read(n, std::cin, true);
}

void print_encoded(BaseEncodedString* es) {
    std::cerr << "Encoded: ";
    if (es->encoding == Encoding::CharacterReplacing) {
        auto encoded = static_cast<CCEncodedString*>(es)->encoded();
        for (uint32_t i = 0; i < strlen(es->decoded()); ++i) {
            std::cout << encoded[i];
        }
    } else if (es->encoding == Encoding::CyclicShift) {
        auto encoded = static_cast<CSEncodedString*>(es)->encoded();
        for (uint32_t i = 0; i < strlen(es->decoded()); ++i) {
            std::cout << encoded[i];
        }
    } else if (es->encoding == Encoding::CharacterReplacingByNumbers) {
        auto encoded = static_cast<CIEncodedString*>(es)->encoded();
        for (uint32_t i = 0; i < strlen(es->decoded()); ++i) {
            std::cout << encoded[i] << ' ';
        }
    }
    std::cout << '\n';
}

void save_input(BaseEncodedString** ess, uint32_t n, std::ostream& ostream) {
    ostream << "Total strings: " << n << '\n';
    ostream << "#,string,encoding,settings\n";
    for (uint32_t i = 0; i < n; ++i) {
        ostream << i + 1 << ',' << ess[i]->decoded() << ',';
        if (ess[i]->encoding == Encoding::CharacterReplacing) {
            ostream << "Char-char" << ',';
            auto mapping = static_cast<CCEncodedString*>(ess[i])->mapping();
            for (uint32_t j = 0; j < alphabet_length; ++j) {
                ostream << mapping[j].to;
            }
        } else if (ess[i]->encoding == Encoding::CharacterReplacingByNumbers) {
            ostream << "Char-int32" << ',';
            auto mapping = static_cast<CIEncodedString*>(ess[i])->mapping();
            for (uint32_t j = 0; j < alphabet_length; ++j) {
                ostream << mapping[j].to << ' ';
            }
        } else {
            ostream << "Shift" << ',';
            auto sf = static_cast<CSEncodedString*>(ess[i])->shift_factor();
            ostream << sf;
        }
        ostream << '\n';
    }
}

void save_output(BaseEncodedString** ess, uint32_t n, std::ostream& ostream) {
    ostream << "\nSorted output:\n";
    ostream << "#,string,encoded\n";
    for (uint32_t i = 0; i < n; ++i) {
        char* decoded = ess[i]->decoded();
        ostream << i << ',' << decoded << ',';
        if (ess[i]->encoding == Encoding::CharacterReplacing) {
            auto encoded = static_cast<CCEncodedString*>(ess[i])->encoded();
            for (uint32_t j = 0; j < strlen(decoded); ++j) {
                ostream << encoded[j];
            }
        } else if (ess[i]->encoding == Encoding::CharacterReplacingByNumbers) {
            auto encoded = static_cast<CIEncodedString*>(ess[i])->encoded();
            for (uint32_t j = 0; j < strlen(decoded); ++j) {
                ostream << encoded[j] << ' ';
            }
        } else {
            auto encoded = static_cast<CSEncodedString*>(ess[i])->encoded();
            for (uint32_t j = 0; j < strlen(decoded); ++j) {
                ostream << encoded[j];
            }
        }
        ostream << '\n';
    }
}