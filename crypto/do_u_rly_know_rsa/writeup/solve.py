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