> # Rev - Encryptor
> > Rev - 100pts
>
> Thou shall not decrypt da flag!

## Writeup
`encryptor.py` encrypts the flag using this algorithm:
```python
def encrypt(text):
    res = ""
    for i, char in enumerate(text):
        res += chr(ord(char) + (i % 4) + 1)
    return res
```

which is just shifting each character by `(i % 4) + 1` where `i` is the index of the character in the string.

This encryption algorithm is reversible, so we can just replace the `+`s with `-`s to get the decryption algorithm:
```python
def decrypt(text):
    res = ""
    for i, char in enumerate(text):
        res += chr(ord(char) - (i % 4) - 1)
    return res
```

The rest of the script is just reading the flag from `flag.txt.enc`, and can be found in [solve.py](./solve.py).

```console
$ python3 solve.py
TD{sn4k3_in_r3vers3_is_3k4ns}
```