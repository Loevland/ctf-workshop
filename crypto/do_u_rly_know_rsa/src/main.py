from Crypto.Util.number import bytes_to_long
import sys

p = int(sys.argv[1])
q = int(sys.argv[2])
n = p * q
e = 65537

flag = open("flag.txt", "rb").read()
flag = bytes_to_long(flag)
ct = pow(flag, e, n)

print("n =", n)
print("e =", e)
print("ct =", ct)