#ifndef IO_H
#define IO_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "encoded_string/cc_string.h"
#include "encoded_string/ci_string.h"
#include "encoded_string/cs_string.h"

BaseEncodedString** read_from_file(uint32_t* n, char* input_filename);
BaseEncodedString** read_from_stdin(uint32_t* n);

void print_encoded(BaseEncodedString* es);
void save_input(BaseEncodedString** ess, uint32_t n, std::ostream& ostream);
void save_output(BaseEncodedString** ess, uint32_t n, std::ostream& ostream);

#endif