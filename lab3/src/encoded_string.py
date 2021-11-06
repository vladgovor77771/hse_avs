ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
ALPHABET_LENGTH = 62


def encode_cc(decoded, new_alphabet):
    encoded = ""
    for i in range(len(decoded)):
        for j in range(ALPHABET_LENGTH):
            if (ALPHABET[j] == decoded[i]):
                encoded += new_alphabet[j]
    return encoded


def encode_ci(decoded, new_alphabet):
    encoded = []
    for i in range(len(decoded)):
        for j in range(ALPHABET_LENGTH):
            if (ALPHABET[j] == decoded[i]):
                encoded.append(new_alphabet[j])
    return encoded


def encode_cs(decoded, offset):
    encoded = ""
    for i in range(len(decoded)):
        cur_index = ALPHABET.index(decoded[i])
        encoded += ALPHABET[(cur_index + offset) % ALPHABET_LENGTH]
    return encoded


class EncodedString:
    def __init__(self, decoded, encoding, settings):
        self.decoded = decoded
        self.encoding = encoding
        self.settings = settings
        self.encoded = None

    def common_func(self):
        sum = 0
        for i in range(len(self.decoded)):
            sum += ord(self.decoded[i])
        return sum * 1.0 / len(self.decoded)

    def encode(self):
        if self.encoding == 1:
            self.encoded = encode_cc(self.decoded, self.settings)
        elif self.encoding == 2:
            self.encoded = encode_cs(self.decoded, self.settings)
        else:
            self.encoded = encode_ci(self.decoded, self.settings)
