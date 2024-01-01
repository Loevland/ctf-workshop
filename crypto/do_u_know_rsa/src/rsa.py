from Crypto.Util.number import getPrime, inverse, bytes_to_long, long_to_bytes

p = getPrime(512)
q = getPrime(512)
n = p * q
e = 65537

flag = open('flag.txt', 'rb').read()
flag = bytes_to_long(flag)

ct = pow(flag, e, n)

print(f'p = {p}')
print(f'q = {q}')
print(f'n = {n}')
print(f'e = {e}')
print(f'ct = {ct}')