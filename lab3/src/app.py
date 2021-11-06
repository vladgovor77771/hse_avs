import sys
from input_output import read_from_stdin, read_from_file, print_encoded, save_input
from sort import sort_array_of_encoded_strings_desc


def main():
    try:
        if (len(sys.argv) == 1):
            ess = read_from_stdin()
            sort_array_of_encoded_strings_desc(ess)
            for i in range(len(ess)):
                ess[i].encode()
                print_encoded(ess[i])
        elif (len(sys.argv) == 2 or len(sys.argv) > 4):
            print(
                "If you want to pass input from file, pass file in path and file out path.")
            print("Optionally, you can pass file path to save input data.")
        else:
            ess = read_from_file(sys.argv[1])
            if (len(sys.argv) == 4):
                fi = open(sys.argv[3], "w")
                save_input(ess, fi)
                fi.close()

            sort_array_of_encoded_strings_desc(ess)
            f = open(sys.argv[2], "a")
            for i in range(len(ess)):
                ess[i].encode()
                print_encoded(ess[i], f)
    except ValueError as e:
        print("Error: " + str(e), file=sys.stderr)


main()
