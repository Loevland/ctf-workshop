from string import ascii_lowercase

# XOR encrypt and decrypt is the same operation
def xor(text, key):
    return bytes([text[i] ^ key[i % len(key)] for i in range(len(text))])

# Find the first 3 bytes of the key by knowing the flag format TD{
known_flag = b"TD{"
flag_enc = open("flag.enc", "rb").read()
known_key = xor(flag_enc, known_flag)[:3]

# Bruteforce the last 2 bytes of the key to find a flag containing lowercase only
alphabet = ascii_lowercase + "_{}TD"
for i in range(256):
    for j in range(256):
        key = known_key + bytes([i, j])
        possible_flag = xor(flag_enc, key)
        if all(c in alphabet.encode() for c in possible_flag):
            print(possible_flag.decode())
            continue
