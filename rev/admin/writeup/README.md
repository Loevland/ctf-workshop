> # Rev - Admin
> > Rev - 50pts
>
> Only those who know the admin password can get the flag

## Writeup
Running `strings` on the binary reveals both the password and the flag.
```console
$ strings admin
<...>
TD{w3lc0m3_4dmin!}
Enter the admin password:
Sup3r_S3cr3t_P4ssw0rd
Wrong!
<...>
```
You see the flag, but can also give the program the password to get the flag printed.

```
TD{w3lc0m3_4dmin!}
```