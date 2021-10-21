#include "ci_string.h"

CIEncodedString::CIEncodedString(char* decoded, int32_t* alphabet_mapping)
    : BaseEncodedString(decoded, Encoding::CharacterReplacing) {
    pairs = new PairCharInt32[alphabet_length];
    for (uint32_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = alphabet_mapping[i];
    }
    delete[] alphabet_mapping;
    encoded_ = new int32_t[strlen(decoded)];
}

CIEncodedString::~CIEncodedString() {
    base_clear();
    delete[] pairs;
    delete[] encoded_;
}

void CIEncodedString::encode() {
    char* str = decoded();
    for (uint32_t i = 0; i < strlen(str); ++i) {
        for (uint32_t j = 0; j < alphabet_length; ++j) {
            if (str[i] == pairs[j].from) {
                encoded_[i] = pairs[j].to;
                break;
            }
        }
    }
}

int32_t* CIEncodedString::encoded() {
    return encoded_;
}

CIEncodedString::PairCharInt32* CIEncodedString::mapping() {
    return pairs;
}