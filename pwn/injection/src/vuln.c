#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void ignore_me(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void timeout(int signal){
    if (signal == SIGALRM){
        printf("You timed out!\n");
        _exit(0);
    }
}

void ignore_me_timeout(){
    signal(SIGALRM, timeout);
    alarm(60);
}


int main(){
    ignore_me();
    ignore_me_timeout();

    size_t nbytes = 0;
    char *line = NULL;
    const char *ls = "ls -al ";

    while (getline(&line, &nbytes, stdin) != -1) {
        line[strlen(line)-1] = '\0';
        size_t bufsize = strlen(ls) + strlen(line) + 2;

        char *buf = calloc(bufsize, sizeof(*buf));
        snprintf(buf, bufsize, "%s%s", ls, line);

        system(buf);
    }

    return 0;
}