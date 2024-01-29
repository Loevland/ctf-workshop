from ctypes import CDLL

# Import libc so we can use the C version of rand() and srand()
libc = CDLL("/lib/x86_64-linux-gnu/libc.so.6")
with open("flag.txt.scrambled", "rb") as f:
    flag_enc = list(f.read())

# Stage 3
libc.srand(0x1337)
for idx, byte in enumerate(flag_enc):
    flag_enc[idx] = byte ^ (libc.rand() & 0xff) # Bitwise AND with 0xff to only get a byte

# Stage 2
for idx, byte in enumerate(flag_enc):
    flag_enc[idx] = byte ^ 0x55

# Stage 1
flag_enc = flag_enc[::-1]
print("".join(chr(x) for x in flag_enc))
