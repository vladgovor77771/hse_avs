#include "cs_string.h"

CSEncodedString::CSEncodedString(char* decoded, int32_t sf)
    : BaseEncodedString(decoded, Encoding::CyclicShift) {
    shift_factor_ = sf;
    encoded_ = new char[strlen(decoded)];
}

CSEncodedString::~CSEncodedString() {
    base_clear();
    delete[] encoded_;
}

void CSEncodedString::encode() {
    char* str = decoded();
    for (uint32_t i = 0; i < strlen(str); ++i) {
        for (int32_t j = 0; j < alphabet_length; ++j) {
            if (str[i] == alphabet[j]) {
                int32_t cur = (j + shift_factor_) % alphabet_length;
                if (cur < 0) {
                    cur += alphabet_length;
                }
                encoded_[i] = alphabet[cur];
                break;
            }
        }
    }
}

char* CSEncodedString::encoded() {
    return encoded_;
}

int32_t CSEncodedString::shift_factor() {
    return shift_factor_;
}