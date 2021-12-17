#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #include <chrono>
// #include <iomanip>

#include "asmproc.h"
#include "encoded_string.h"

void set_random_str(struct EncodedString* es, int length) {
    for (int i = 0; i < length; ++i) {
        es->str[i] = alphabet[rand() % alphabet_length];
    }
    es->str[length] = '\0';
}

void benchmark_encode_char_char(int str_length) {
    struct EncodedString* es = (struct EncodedString*)malloc(sizeof(struct EncodedString));
    es->str = (char*)malloc(sizeof(char) * 500);
    set_random_str(es, str_length);
    es->encoded.str = (char*)malloc(sizeof(char) * 500);
    es->encoding = ReplaceChar;
    es->settings.chars = (char*)malloc(sizeof(char) * (alphabet_length + 1));

    for (int i = 0; i < alphabet_length; ++i) {
        es->settings.chars[i] = alphabet[rand() % alphabet_length];
    }

    clock_t t1, t2;
    t1 = clock();
    EncryptData(es);
    t2 = clock();
    double time_taken = ((double)(t2 - t1)) / CLOCKS_PER_SEC * 1000000000;
    printf("Char-char encoding of string with length %d: %f nanoseconds\n", str_length, time_taken);

    free(es->str);
    free(es->encoded.str);
    free(es->settings.chars);
    free(es);
}

void benchmark_encode_char_int32(int str_length) {
    struct EncodedString* es = (struct EncodedString*)malloc(sizeof(struct EncodedString));
    es->str = (char*)malloc(sizeof(char) * 500);
    set_random_str(es, str_length);
    es->encoded.str = (char*)malloc(sizeof(char) * 500);
    es->encoding = ReplaceNum;
    es->settings.nums = (u_int8_t*)malloc(sizeof(u_int8_t) * (alphabet_length + 1));

    for (int i = 0; i < alphabet_length; ++i) {
        es->settings.nums[i] = alphabet[rand() % 256];
    }

    clock_t t1, t2;
    t1 = clock();
    EncryptData(es);
    t2 = clock();
    double time_taken = ((double)(t2 - t1)) / CLOCKS_PER_SEC * 1000000000;
    printf("Char-int32 encoding of string with length %d: %f nanoseconds\n", str_length,
           time_taken);

    free(es->str);
    free(es->encoded.str);
    free(es->settings.chars);
    free(es);
}

void benchmark_encode_shift(int str_length) {
    struct EncodedString* es = (struct EncodedString*)malloc(sizeof(struct EncodedString));
    es->str = (char*)malloc(sizeof(char) * 500);
    set_random_str(es, str_length);
    es->encoded.str = (char*)malloc(sizeof(char) * 500);
    es->encoding = Shift;
    es->settings.shift_factor = rand() % alphabet_length;

    clock_t t1, t2;
    t1 = clock();
    EncryptData(es);
    t2 = clock();
    double time_taken = ((double)(t2 - t1)) / CLOCKS_PER_SEC * 1000000000;
    printf("Shift encoding of string with length %d: %f nanoseconds\n", str_length, time_taken);

    free(es->str);
    free(es->encoded.str);
    free(es);
}

void benchmark_sort(int n) {
    struct EncodedString** ess = (struct EncodedString**)malloc(sizeof(struct EncodedString*) * n);
    for (int i = 0; i < n; ++i) {
        ess[i] = (struct EncodedString*)malloc(sizeof(struct EncodedString));
        ess[i]->str = (char*)malloc(sizeof(char) * 500);
        set_random_str(ess[i], 50);
        ess[i]->encoded.str = (char*)malloc(sizeof(char) * 500);
    }

    // Здесь обязательное предварительное вычисление ключей и запись в память
    for (int i = 0; i < n; i++) {
        ess[i]->key = CalcKey(ess + i);
    }

    clock_t t1, t2;
    t1 = clock();
    DoSort(ess, n);
    t2 = clock();
    double time_taken = ((double)(t2 - t1)) / CLOCKS_PER_SEC * 1000000000;

    printf("Sort of %d strings: %f nanoseconds\n", n, time_taken);

    for (int i = 0; i < n; ++i) {
        free(ess[i]->str);
        free(ess[i]->encoded.str);
        free(ess[i]);
    }
    free(ess);
}

int main() {
    srand(time(NULL));

    benchmark_sort(50);
    benchmark_sort(100);
    benchmark_sort(500);
    benchmark_sort(1000);
    benchmark_sort(5000);
    benchmark_sort(10000);
    benchmark_sort(20000);

    benchmark_encode_char_char(50);
    benchmark_encode_char_char(100);
    benchmark_encode_char_char(200);
    benchmark_encode_char_char(300);
    benchmark_encode_char_char(400);
    benchmark_encode_char_char(499);

    benchmark_encode_char_int32(50);
    benchmark_encode_char_int32(100);
    benchmark_encode_char_int32(200);
    benchmark_encode_char_int32(300);
    benchmark_encode_char_int32(400);
    benchmark_encode_char_int32(499);

    benchmark_encode_shift(50);
    benchmark_encode_shift(100);
    benchmark_encode_shift(200);
    benchmark_encode_shift(300);
    benchmark_encode_shift(400);
    benchmark_encode_shift(499);

    return 0;
}
