#include "encoded_string.h"
#include "io.h"
#include "sort.h"

// int32_t bs_loc(int32_t a[], int32_t item, int32_t low, int32_t high) {
//     while (low <= high) {
//         int mid = low + (high - low) / 2;
//         if (item == a[mid])
//             return mid + 1;
//         else if (item > a[mid])
//             high = mid - 1;
//         else
//             low = mid + 1;
//     }

//     return low;
// }

// void sort_bs(int32_t* a, int32_t n) {
//     int32_t i, j, loc, selected;

//     for (i = 1; i < n; ++i) {
//         j = i - 1;
//         selected = a[i];
//         loc = bs_loc(a, selected, 0, i);
//         while (j >= loc) {
//             a[j + 1] = a[j];
//             --j;
//         }
//         a[j + 1] = selected;
//     }
// }

int main() {
    // int32_t ints[] = {1, 3, 5, 7, 5, 4, 6, 2, 1};
    // int32_t ints[] = {1, 6, 2, 7, 8, 3, 65, 8, 5, 3, 10, 5, 7};
    // sort_bs(ints, 13);
    // for (int i = 0; i < 13; i++) {
    //     std::cout << ints[i] << ' ';
    // }
    // std::cout << '\n';
    // std::cout << bs_loc(ints, 2, 5, 7) << '\n';
    std::cin.tie(NULL);
    std::cerr << "Input amount of strings need to be encoded: ";
    uint32_t n;
    std::cin >> n;
    EncodedString** ess = new EncodedString*[n];
    for (uint32_t i = 0; i < n; ++i) {
        ess[i] = create_es();
    }

    try {
        for (uint32_t i = 0; i < n; ++i) {
            read_str(ess[i]->str);
            read_encoding(ess[i]);
            encode(ess[i]);
        }

        std::cerr << '\n';
        sort_array_of_encoded_strings_desc(ess, static_cast<int32_t>(n));
        for (uint32_t i = 0; i < n; ++i) {
            std::cerr << "Key: " << common_func(ess[i]) << ' ';
            print_encoded(ess[i]);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    for (uint32_t i = 0; i < n; ++i) {
        clear_es(ess[i]);
        delete ess[i];
    }
    delete[] ess;
    return 0;
}