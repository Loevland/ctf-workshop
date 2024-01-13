> # Crypto - Do u rly know RSA?
> > Crypto - 150pts
>
> This time I remebered to remove `p` and `q` from my script.

## Writeup
We are given the ciphertext `ct`, the public key `e` and the modulus `n` (which looks large).

We can check with [factordb](http://factordb.com/) is the modulus `n` has known factors, which it does.
```
p = 32769132993266709549961988190834461413177642967992942539798288533
q = 3490529510847650949147849619903898133417764638493387843990820577
```

Knowing the two factors we can decrypt the ciphertext as normal.
```python
from Crypto.Util.number import inverse, long_to_bytes

with open("out.txt", "r") as f:
    n = int(f.readline().split(" = ")[1])
    e = int(f.readline().split(" = ")[1])
    ct = int(f.readline().split(" = ")[1])

# From factordb.com we can get the factors of n
p = 32769132993266709549961988190834461413177642967992942539798288533
q = 3490529510847650949147849619903898133417764638493387843990820577

phi = (p - 1) * (q - 1)
d = inverse(e, phi)
flag = pow(ct, d, n)
print(long_to_bytes(flag).decode())
```

```bash
$ python3 solve.py
TD{w0w_y0u_rly_kn0w_rsa}
```