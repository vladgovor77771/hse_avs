#ifndef CC_STRING_H
#define CC_STRING_H
#include "base.h"

// char int32 pairing
class CIEncodedString : public BaseEncodedString {
public:
    struct PairCharInt32 {
        char from;
        int32_t to;
    };
    PairCharInt32* mapping();
    CIEncodedString(char* decoded, int32_t* alphabet_mapping);
    void encode();
    int32_t* encoded();
    ~CIEncodedString();

private:
    PairCharInt32* pairs;
    int32_t* encoded_;
};

#endif
