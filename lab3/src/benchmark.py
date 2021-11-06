from sort import sort_array_of_encoded_strings_desc
from encoded_string import EncodedString, ALPHABET, ALPHABET_LENGTH
import string
import random
from random import randrange
import time


def random_string(size):
    return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(size))


def benchmark_sort(amount):
    ess = []
    for i in range(amount):
        es = EncodedString(random_string(50), 2, 1)
    t1 = time.time_ns()
    sort_array_of_encoded_strings_desc(ess)
    t2 = time.time_ns()
    print("Sort of " + str(amount) + " string: " + str(t2 - t1) + " nanoseconds")


def benchmark_encode_char_char(string_size):
    es = EncodedString(random_string(string_size), 1,
                       random_string(ALPHABET_LENGTH))
    t1 = time.time_ns()
    es.encode()
    t2 = time.time_ns()
    print("Char-char encoding of string with length " +
          str(string_size) + ": " + str(t2 - t1) + " nanoseconds")


def benchmark_encode_char_int32(string_size):
    mapping = []
    for i in range(ALPHABET_LENGTH):
        mapping.append(randrange(ALPHABET_LENGTH))
    es = EncodedString(random_string(string_size), 3, mapping)
    t1 = time.time_ns()
    es.encode()
    t2 = time.time_ns()
    print("Char-int32 encoding of string with length " +
          str(string_size) + ": " + str(t2 - t1) + " nanoseconds")


def benchmark_encode_shift(string_size):
    es = EncodedString(random_string(string_size), 2,
                       randrange(ALPHABET_LENGTH))
    t1 = time.time_ns()
    es.encode()
    t2 = time.time_ns()
    print("Cyclic shift of string with length " +
          str(string_size) + ": " + str(t2 - t1) + " nanoseconds")


def main():
    benchmark_sort(50)
    benchmark_sort(100)
    benchmark_sort(500)
    benchmark_sort(1000)
    benchmark_sort(5000)
    benchmark_sort(10000)
    benchmark_sort(50000)
    benchmark_sort(100000)
    benchmark_sort(200000)

    benchmark_encode_char_char(50)
    benchmark_encode_char_char(100)
    benchmark_encode_char_char(200)
    benchmark_encode_char_char(300)
    benchmark_encode_char_char(400)
    benchmark_encode_char_char(499)

    benchmark_encode_char_int32(50)
    benchmark_encode_char_int32(100)
    benchmark_encode_char_int32(200)
    benchmark_encode_char_int32(300)
    benchmark_encode_char_int32(400)
    benchmark_encode_char_int32(499)

    benchmark_encode_shift(50)
    benchmark_encode_shift(100)
    benchmark_encode_shift(200)
    benchmark_encode_shift(300)
    benchmark_encode_shift(400)
    benchmark_encode_shift(499)


main()
