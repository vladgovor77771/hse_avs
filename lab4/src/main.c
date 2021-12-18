#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asmproc.h"
#include "encoded_string.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Using: file input, file output\n");
        return 1;
    }

    int cnt;
    int v;
    // Массив указателей на структуры
    struct EncodedString** arr;

    char buf[255];
    // Читаем структуры из файла
    FILE* f = fopen(argv[1], "r");
    fscanf(f, "%d", &cnt);
    arr = (struct EncodedString**)malloc(sizeof(struct EncodedString*) * cnt);

    for (int i = 0; i < cnt; i++) {
        fscanf(f, "%s", buf);

        // Создаем указатели и выделяем память
        arr[i] = (struct EncodedString*)malloc(sizeof(struct EncodedString));
        arr[i]->str = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        arr[i]->encoded.str = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        // помещаем строку в структуру
        strcpy(arr[i]->str, buf);

        // читаем тип шифрования
        fscanf(f, "%d", &v);
        // для каждого типа шифрования, считываем свои данные
        if (v == 1) {
            arr[i]->encoding = Shift;
            fscanf(f, "%d", &arr[i]->settings.shift_factor);
        }
        if (v == 2) {
            arr[i]->encoding = ReplaceChar;
            arr[i]->settings.chars = (char*)malloc(sizeof(char) * (alphabet_length + 1));
            fscanf(f, "%s", arr[i]->settings.chars);
        }
        if (v == 3) {
            arr[i]->encoding = ReplaceNum;
            arr[i]->settings.nums = (u_int8_t*)malloc(sizeof(u_int8_t) * (alphabet_length));
            // для третьего типа - отдельно читаем числа
            for (int j = 0; j < alphabet_length; j++) {
                fscanf(f, "%hhu", arr[i]->settings.nums + j);
            }
        }
    }
    fclose(f);

    // Вызов сортировки с предварительным вычислением ключей
    for (int i = 0; i < cnt; i++) {
        arr[i]->key = CalcKey(arr + i);
    }
    DoSort(arr, cnt);
    // Вызов шифрования
    for (int i = 0; i < cnt; i++) {
        EncryptData(arr[i]);
    }

    // Вывод исходных и зашифрованных данных в файл
    FILE* fo = fopen(argv[2], "w");
    for (int i = 0; i < cnt; i++) {
        fprintf(fo, "%s => ", arr[i]->str);
        // Для шифрования на числа - выводим массив чисел
        if (arr[i]->encoding == ReplaceNum) {
            for (int j = 0; j < strlen(arr[i]->str); j++) {
                fprintf(fo, "%d ", arr[i]->encoded.nums[j]);
            }
            fprintf(fo, "\n");
        } else {
            // иначе просто закодированную строку
            fprintf(fo, "%s\n", arr[i]->encoded.str);
        }
    }
    fclose(fo);

    // Очистка всей выделенной памяти
    for (int i = 0; i < cnt; i++) {
        free(arr[i]->str);
        free(arr[i]->encoded.str);
        if (arr[i]->encoding != Shift) {
            free(arr[i]->settings.chars);
        }
        free(arr[i]);
    }
    free(arr);

    return 0;
}
