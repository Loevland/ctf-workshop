# Big Data Database

> > Web - 100pts

> Our new web developer has created a login page for us. He says the
> database is secure, but I'm not so sure. Can you get in?

> The website is located at: `REPLACE ME`

By mentioning the password being stored in a database, and the name of the challenge, one of the first things one would 
think of, is that the server doesn't handle their storing of password and usernames properly. When reading up on this, 
a commonly used SQL injection for gathering the first username and password stored in a database, is ' OR 1=1; -- . 
If inserting this in the username field, the website will register you as logged in, and yield the flag: 
TD{SQL_1nj3ct10n_1s_4w3s0m3}.