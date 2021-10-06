#ifndef SORT_H
#define SORT_H

#include "encoded_string.h"

int32_t common_func(EncodedString* es);
void sort_array_of_encoded_strings_desc(EncodedString** ess, int32_t n);

#endif