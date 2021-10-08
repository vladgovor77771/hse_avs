#ifndef IO_H
#define IO_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "encoded_string.h"

EncodedString** read_from_file(uint32_t* n, char* input_filename);
EncodedString** read_from_stdin(uint32_t* n);

void print_encoded(EncodedString* es);
void save_input(EncodedString** ess, uint32_t n, std::ostream& ostream);
void save_output(EncodedString** ess, uint32_t n, std::ostream& ostream);

#endif