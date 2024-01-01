FROM ubuntu:22.04
LABEL Description="Overflow 1"

RUN useradd -d /home/ctf -m -p ctf -s /bin/bash ctf
WORKDIR /home/ctf

COPY ynetd .
COPY overflow1 .
COPY flag.txt .

RUN chown -R root:root /home/ctf
RUN chmod -R a+rx /home/ctf

USER ctf
CMD ./ynetd -p 9000 ./overflow1