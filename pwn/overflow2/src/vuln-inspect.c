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

void win(){
    print_flag();
}

#ifndef OFFSET
#define OFFSET 40
#endif
void printstack(char *name);
void doeit();

int main(){
    ignore_me();
    ignore_me_timeout();
    
    doeit();

    return 0;
}

void doeit(){
    char name[32];

    // printf("&main := %p \n", main);
    // printf("&win  := %p \n", win);
    // printf("rip   := %p (before gets) \n", *(long long**)(name+OFFSET));

    printstack(name);

    puts("What is your name?");
    gets(name);

    // printf("rip   := %p (after gets) \n", *(long long**)(name+OFFSET));
    // *(long long**)(name+OFFSET) = (long long*)win;

    printstack(name);
}

void printstack(char *name) {
    for(unsigned char *addr = (long long)(name+0xff) & ~0xff; addr >= name-0x10; addr -= 8){
        printf(" | %p ", addr);
        printf(" | %02x %02x %02x %02x %02x %02x %02x %02x ",
                addr[7], addr[6], addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
        if(addr == name) {
            printf(" | %4s%4s ", "name", "");
        } else if(addr == name+OFFSET) {
            printf(" | %4s+%3d ", "name", OFFSET, "");
        } else {
            printf(" | %4s%4s ", "", "");
        }
        printf(" |\n");
    }
}
