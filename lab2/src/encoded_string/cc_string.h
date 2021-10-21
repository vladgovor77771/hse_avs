#ifndef CI_STRING_H
#define CI_STRING_H
#include "base.h"

// char char pairing
class CCEncodedString : public BaseEncodedString {
public:
    struct PairCharChar {
        char from;
        char to;
    };
    PairCharChar* mapping();
    CCEncodedString(char* decoded, char* alphabet_mapping);
    void encode();
    char* encoded();
    ~CCEncodedString();

private:
    PairCharChar* pairs;
    char* encoded_;
};

#endif
