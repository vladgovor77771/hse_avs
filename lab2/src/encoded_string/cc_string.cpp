#include "cc_string.h"

CCEncodedString::CCEncodedString(char* decoded, char* alphabet_mapping)
    : BaseEncodedString(decoded, Encoding::CharacterReplacing) {
    pairs = new PairCharChar[alphabet_length];
    for (uint32_t i = 0; i < alphabet_length; ++i) {
        pairs[i].from = alphabet[i];
        pairs[i].to = alphabet_mapping[i];
    }
    delete[] alphabet_mapping;
    encoded_ = new char[strlen(decoded)];
}

CCEncodedString::~CCEncodedString() {
    base_clear();
    delete[] pairs;
    delete[] encoded_;
}

void CCEncodedString::encode() {
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

char* CCEncodedString::encoded() {
    return encoded_;
}

CCEncodedString::PairCharChar* CCEncodedString::mapping() {
    return pairs;
}