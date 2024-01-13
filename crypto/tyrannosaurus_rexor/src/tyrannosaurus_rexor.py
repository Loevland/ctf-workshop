from os import urandom

def encrypt(text, key):
    return bytes([text[i] ^ key[i % len(key)] for i in range(len(text))])

flag = open("flag.txt", "rb").read()
key = urandom(5)

with open("flag.enc", "wb") as f:
    f.write(encrypt(flag, key))