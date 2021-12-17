#include <stdlib.h>

const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
// длина словаря
const int alphabet_length = 62;

// Типы шифрования - сдвиг, замена символа, замена на число
enum Encoding { Shift, ReplaceChar, ReplaceNum };

// Указываем упаковку по байту
#pragma pack(push, 1)
struct EncodedString {
    char* str;               // Указатель на строку - 8 байт
    enum Encoding encoding;  // Тип шифрования - 4 байта
    union EncodeParams {  // Объединение данных шифрования - 8 байт
        int32_t shift_factor;  // сдвиг
        char* chars;           // либо алфавит замены
        u_int8_t* nums;        // либо числа замены
    } settings;
    union EncodedResult {  // Объединение данных закодированной строки - 8 байт
        char* str;       // либо выходная строка
        u_int8_t* nums;  // либо массив чисел. Использует тип 8 бит для упрощения работы с памятью
    } encoded;
    float key;  // Ключ, сохраненный в памяти
};
