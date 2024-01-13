> # Rev - Password Check
> > Rev - 50pts
>
> I hid the flag behind this super secure password checker. I also deleted the source code so that no one can ever find it!

## Writeup
### Solution 1
The challenge gives us a binary file, `password_checker`, which asks for a password when run.

Because we have a binary file we can decompile it with IDA (or Ghidra) to see what the program does. When you have loaded the program into IDA, you can press `f5` do get a decompiled view of the program (which will be close to the actual source code).

It shows this `main` function:
```c
int __fastcall main(int argc, const char **argv, const char **envp){
  __int64 buf[6]; // [rsp+0h] [rbp-30h] BYREF

  buf[5] = __readfsqword(0x28u);
  memset(buf, 0, 32);
  printf("Enter the password: ");
  fflush(_bss_start);
  read(0, buf, 0x20uLL);
  if ( (unsigned int)check_password(buf) )
    puts("Correct!");
  else
    puts("Wrong!");
  return 0;
}
```

The program reads in 32 bytes (characters) and calls the `check_password` function. Double-clicking on this function shows us the following code for it:
```c
_BOOL8 __fastcall check_password(const char *a1){
  if ( strlen(a1) != 32 )
    return 0LL;
  if ( strncmp(a1, "TD{youw", 7uLL) )
    return 0LL;
  if ( strncmp(a1 + 7, "illno", 5uLL) )
    return 0LL;
  if ( strncmp(a1 + 12, "tguess", 6uLL) )
    return 0LL;
  if ( !strncmp(a1 + 22, "password!}", 0xAuLL) )
    return strncmp(a1 + 18, "this", 4uLL) == 0;
  return 0LL;
}
```

Knowing that `a1` is the argument passed from `main`, which is our supplied password, we can see that the password has to be 32 characters long. It also contains the following parts:
- `TD{youw`
- `illno`
- `tguess`
- `this`
- `password!}`

The flag is the password, which is `TD{youwillnotguessthispassword!}`.


### Solution 2
If we run `strings password_checker`, we will see the following strings in the binary:
```
TD{youw
illno
tguess
password!}
this
Enter the password:
Correct!
Wrong!
```
From this we can deduce that the flag is `TD{youwillnotguessthispassword!}`, which we can verify by running the binary and give it as the password.
```bash
$ ./password_check
Enter the password: TD{youwillnotguessthispassword!}
Correct!
```