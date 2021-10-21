#ifndef CS_STRING_H
#define CS_STRING_H
#include "base.h"

// char shift
class CSEncodedString : public BaseEncodedString {
public:
    int32_t shift_factor();
    CSEncodedString(char* decoded, int32_t sf);
    void encode();
    char* encoded();
    ~CSEncodedString();

private:
    int32_t shift_factor_;
    char* encoded_;
};

#endif
