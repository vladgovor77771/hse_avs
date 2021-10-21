#include "base.h"

BaseEncodedString::BaseEncodedString(char* decoded, Encoding enc) {
    str = decoded;
    encoding = enc;
}

void BaseEncodedString::base_clear() {
    delete[] str;
}

char* BaseEncodedString::decoded() {
    return str;
}

int32_t BaseEncodedString::common_func() {
    int32_t sum = 0;
    size_t length = strlen(str);
    for (uint32_t i = 0; i < length; ++i) {
        sum += static_cast<int32_t>(str[i]);
    }
    return sum / length;
}
