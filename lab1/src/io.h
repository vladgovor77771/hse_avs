#ifndef IO_H
#define IO_H

#include <cstdint>
#include <cstring>
#include <iostream>

#include "encoded_string.h"

void read_str(char* buffer);
void read_encoding(EncodedString* es);
void print_encoded(EncodedString* es);
void print_str(EncodedString* es);

#endif