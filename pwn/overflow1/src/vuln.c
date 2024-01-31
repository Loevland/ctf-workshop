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

void print_flag(){
    char chr;
    FILE *f = fopen("flag.txt", "r");
    chr = fgetc(f);
    while (chr != EOF){
        printf("%c", chr);
        chr = fgetc(f);
    }
    printf("\n");
    fclose(f);
}


int main(){
    ignore_me();
    ignore_me_timeout();

    char name[32];
    long int admin = 0;

    puts("What is your name?");
    gets(name);

    if(admin != 0){
        print_flag();
    }
    else{
        puts("You are not an admin :(");
    }

    return 0;
}