def decrypt(text):
    res = ""
    for i, char in enumerate(text):
        res += chr(ord(char) - (i % 4) - 1)
    return res

with open("flag.txt.enc", "r") as f:
    ct = f.read()

print(decrypt(ct))
