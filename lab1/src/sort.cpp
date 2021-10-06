#include "sort.h"

int32_t common_func(EncodedString *es) {
    int32_t sum = 0;
    size_t length = strlen(es->str);
    for (uint32_t i = 0; i < length; ++i) {
        sum += static_cast<int32_t>(es->str[i]);
    }
    return sum / length;
}

int32_t binary_search_location(int32_t a[], int32_t item, int32_t low, int32_t high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item == a[mid])
            return mid + 1;
        else if (item > a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return low;
}

void sort_array_of_encoded_strings_desc(EncodedString **ess, int32_t n) {
    int32_t *keys = new int32_t[n];
    for (int32_t i = 0; i < n; ++i) {
        keys[i] = common_func(ess[i]);
    }

    int32_t i, j, loc, selected;
    EncodedString *selected_es;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = keys[i];
        selected_es = ess[i];
        loc = binary_search_location(keys, selected, 0, i);
        while (j >= loc) {
            keys[j + 1] = keys[j];
            ess[j + 1] = ess[j];
            --j;
        }
        keys[j + 1] = selected;
        ess[j + 1] = selected_es;
    }

    delete[] keys;
}
