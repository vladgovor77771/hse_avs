from encoded_string import EncodedString, ALPHABET, ALPHABET_LENGTH


def read_enc_settings_from_stdin(enc_id):
    if enc_id == 1:
        print("Total " + str(ALPHABET_LENGTH) + " chars need to be shuffled")
        print("Input mapping: |" + ALPHABET + "|")
        print("             :  ", end="")
        res = input()
        if len(res) != ALPHABET_LENGTH:
            raise ValueError("Incorrent encoding settings.")
        return res
    elif enc_id == 2:
        print("Input offset: ", end="")
        return int(input())
    else:
        print("Total " + str(ALPHABET_LENGTH) + " chars need to be shuffled")
        print("Input each after each: ", end="")
        res = []
        for i in range(ALPHABET_LENGTH):
            res.append(int(input()))
            return res


def read_from_file(path):
    f = open(path, "r")
    n = int(f.readline())
    ess = []
    for i in range(n):
        cur = f.readline().strip()
        try:
            enc_id = int(f.readline())
            if enc_id < 1 or enc_id > 3:
                raise ValueError()
        except Exception:
            raise ValueError("unknown encoding")
        enc_settings = None
        if enc_id == 1:
            enc_settings = f.readline().strip()
        elif enc_id == 3:
            enc_settings = list(
                map(lambda x: int(x), f.readline().strip().split(" ")))
        else:
            enc_settings = int(f.readline().strip())
        ess.append(EncodedString(cur, enc_id, enc_settings))
    f.close()
    return ess


def read_from_stdin():
    print('Input amount of strings need to be encoded: ', end='')
    n = int(input())
    ess = []
    for i in range(n):
        print('Input string: ', end='')
        cur = input()
        print("Specify encoding:\n1. Replace chars by chars\n2. Cyclic shift\n3. Replace chars "
              "by numbers\nInput: ", end='')
        enc_id = int(input())
        if enc_id < 1 and enc_id > 3:
            raise ValueError('Incorrect encoding.')
        enc_settings = read_enc_settings_from_stdin(enc_id)
        ess.append(EncodedString(cur, enc_id, enc_settings))
    return ess


def print_encoded(es, file=None):
    if file is not None:
        if es.encoding == 3:
            file.write(" ".join(list(map(lambda x: str(x), es.encoded))) + "\n")
        else:
            file.write(es.encoded + "\n")
    else:
        if es.encoding == 3:
            print(" ".join(list(map(lambda x: str(x), es.encoded))))
        else:
            print(es.encoded)


def save_input(ess, file):
    file.write("Total strings: " + str(len(ess)) + "\n")
    file.write("#,string,encoding,settings\n")
    for i in range(len(ess)):
        file.write(str(i+1) + "," + ess[i].decoded + ",")
        if ess[i].encoding == 1:
            file.write("Char-char," + ess[i].settings)
        elif ess[i].encoding == 2:
            file.write("Shift," + str(ess[i].settings))
        else:
            file.write("Char-int32," +
                       " ".join(list(map(lambda x: str(x), ess[i].settings))))
        file.write("\n")
