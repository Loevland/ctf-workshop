
def encrypt(text):
    res = ""
    for i, char in enumerate(text):
        res += chr(ord(char) + (i % 4) + 1)
    return res

with open("flag.txt", "r") as f:
    flag = f.read()

with open("flag.txt.enc", "w") as f:
    f.write(encrypt(flag))
