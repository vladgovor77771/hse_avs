#ifndef BASE_STRING_H
#define BASE_STRING_H
#include <cstdint>
#include <cstring>

const uint32_t string_buffer_size = 500;
const int32_t alphabet_length = 62;
const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

enum Encoding { CharacterReplacing, CyclicShift, CharacterReplacingByNumbers };

// base
class BaseEncodedString {
private:
    char* str;  // decoded

public:
    Encoding encoding;
    BaseEncodedString(char* decoded, Encoding enc);
    void base_clear();
    char* decoded();
    int32_t common_func();
    virtual void encode() = 0;
    virtual ~BaseEncodedString(){};
};

#endif
