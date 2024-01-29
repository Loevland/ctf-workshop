> # Rev - Scramblinator
> > Rev - 150pts
>
> Let me introduce you to my new encryption program, the Scramblinator!

## Writeup
Loading the `scramblinator` program into IDA we see this version of the `main` function (with a little bit of cleanup done):
```c
int main(int argc, const char **argv, const char **envp) {
  FILE *stream;
  char content[64];

  if ( argc != 2 ) {
    puts("Usage: scramblinator <filename>");
    exit(1);
  }
  stream = fopen(argv[1], "r");
  if ( !stream ) {
    puts("Error opening file");
    exit(1);
  }
  memset(content, 0, sizeof(content));
  fgets(content, 64, stream);
  fclose(stream);
  stage1(content);
  stage2(content);
  stage3(content);
  write_to_file(argv[1], content);
  return 0;
}
```

We can see that the program reads the contents of a file, and then passes the file contents through 3 stages/functions, before `write_to_file` is called (which just writes the file contents back to a file with the `.scrambled` extension added).

### Stage 1
The cleaned up version of `stage1` is:
```c
void stage1(const char *content) {
  char tmp;
  int j;
  int i;

  for (j=0, i=strlen(content)-1; j < i;--i){
    tmp = content[j];
    content[j] = content[i];
    content[i] = tmp;
    ++j;
  }
}
```
which swaps the first character with the last, the second with the second last, etc. This is a simple reverse function.

### Stage 2
The second stage performs an XOR operation on each character/byte in the file contents buffer with the key `0x55`.
```c
void stage2(const char *content){
  int i;
  for (i = 0; i<strlen(content);++i)
    content[i] ^= 0x55u;
}
```

### Stage 3
The third stage sets a `seed` to `0x1337` and XORs each character/byte in the file contents buffer with `rand()` as the key.
```c
void stage3(const char *content) {
  int i;

  srand(0x1337u);
  for ( i = 0; i < strlen(content); ++i ) {
    content[i] = content[i] ^ rand();
  }
}
```

### Solving the challenge
To solve the challenge we can perform the stages in reverse order to get the original file contents back. A python-solution can be found in [solve.py](./solve.py).

```console
$ python3 solve.py
TD{scr4mbl3d_0r_un5cr4mbl3d_3gg5?}
```