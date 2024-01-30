> # Crypto - Tyrannosaurus rexor
> > Crypto - 150pts
>
> I accidentally ran my flag through this program, and now it's all garbled up! Can you help me recover it?
>
> I remember that the flag starts with `TD{`, ends with `}`, and only contains lowercase and underscore characters otherwise...


## Writeup
The `encrypt` function in the python script uses XOR to encrypt the flag. The `key` is generated at random, but only consists of 5 bytes. This means that the key can be bruteforced.

We already know that the flag starts with the letters `TD{`, so we can revocer the first 3 bytes of the key by XORing the first 3 bytes of the encrypted flag with `TD{`.
```python
# XOR encrypt and decrypt is the same operation
def xor(text, key):
    return bytes([text[i] ^ key[i % len(key)] for i in range(len(text))])

# Find the first 3 bytes of the key by knowing the flag format TD{
known_flag = b"TD{"
flag_enc = open("flag.enc", "rb").read()
known_key = xor(flag_enc, known_flag)[:3]
```

We don't know the last 2 bytes of the key, so we have to bruteforce that part and look at the potential flags that only contains lowercase and underscore characters.
```python
from string import ascii_lowercase

# Bruteforce the last 2 bytes of the key to find a flag containing lowercase only
alphabet = ascii_lowercase + "_{}TD"
for i in range(256):
    for j in range(256):
        key = known_key + bytes([i, j])
        possible_flag = xor(flag_enc, key)
        if all(c in alphabet.encode() for c in possible_flag):
            print(possible_flag.decode())
            continue
```

The script output 20 flags that all are potential flags, but only 1 of them uses words which actually form a sentence.

```console
$ python3 solve.py
<...>
TD{xor_strong_but_not_with_small_key}
<...>
```
