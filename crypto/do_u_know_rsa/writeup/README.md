> # Crypto - Do you know RSA?
> > Crypto - 50pts
>
> Do you know how RSA works?

## Writeup
In RSA `p` and `q` are supposed to be secret, but in this challenge we are given them both. This lets us calculate `phi = (p-1)(q-1)` and `d = e^-1 mod phi`. We can then decrypt the ciphertext using `m = c^d mod n`.

`ìnverse` and `bytes_to_long` have been imported in the original script as a hint to use them. The solve script can be found in [solve.py](./solve.py).

```console
$ python3 solve.py
TD{s3cur3_y0ur_ps_and_qs}
```