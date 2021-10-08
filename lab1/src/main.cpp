#include "encoded_string.h"
#include "io.h"
#include "sort.h"

int main(int argc, char** argv) {
    std::cin.tie(NULL);
    uint32_t n = 0;
    EncodedString** ess = NULL;
    try {
        if (argc == 1) {
            ess = read_from_stdin(&n);
            sort_array_of_encoded_strings_desc(ess, static_cast<int32_t>(n));
            for (uint32_t i = 0; i < n; ++i) {
                encode(ess[i]);
                print_encoded(ess[i]);
            }
        } else if (argc == 2) {
            std::cout << "required parameters input.file output.file\n";
        } else if (argc == 3) {
            ess = read_from_file(&n, argv[1]);
            std::ofstream outfile;
            outfile.open(argv[2], std::ios_base::out);
            save_input(ess, n, outfile);
            sort_array_of_encoded_strings_desc(ess, static_cast<int32_t>(n));
            for (uint32_t i = 0; i < n; ++i) {
                encode(ess[i]);
            }
            save_output(ess, n, outfile);
            outfile.close();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    if (ess) {
        for (uint32_t i = 0; i < n; ++i) {
            if (ess[i]) {
                clear_es(ess[i]);
                delete ess[i];
            }
        }
        delete[] ess;
    }

    return 0;
}