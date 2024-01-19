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

void printstack(char *prefix, char *name) {
    unsigned char *addr;
    char line[512], variable[32];
    
    printf("%s\n", prefix);
    snprintf(line, sizeof(line),
        "+%s+\n| %14s | %15s%8s | %10s |\n+%s+",
        "----------------+-------------------------+------------",
        "Memory Address", "HEXDUMP", "", "Variable",
        "----------------+-------------------------+------------"
    );
    printf("%s\n", line);
    for(addr = (long long)(name+0x100) & ~0xff; /* Round up pointer to nearest 0x...00 */
        addr >= name-0x10; /* From rounded address until past name and a little more. */
        addr -= 8 /* Print stack in descending order. */
        ){
        /* Format right-most variable column. */
        if(addr == name) {
            snprintf(variable, sizeof(variable), "%s%3s", "name", "");
        } else if(addr == name+OFFSET) {
            snprintf(variable, sizeof(variable), "%s+%2d", "name", OFFSET);
        } else {
            *variable = 0;
        }
        /* Output 8-byte aligned stack-memory. */
        snprintf(line, sizeof(line),
            "| %14p | %02x %02x %02x %02x %02x %02x %02x %02x | %10s |",
            addr, addr[7], addr[6], addr[5], addr[4], addr[3], addr[2], addr[1], addr[0], variable
        );
        printf("%s\n", line);
    }
    snprintf(line, sizeof(line), "+%s+",
        "----------------+-------------------------+------------");
    printf("%s\n", line);
}

int main(){
    ignore_me();
    ignore_me_timeout();
    
    char name[32];

    printstack("Before 'gets(name)'", name);

    puts("What is your name?");
    gets(name);

    printstack("After 'gets(name)'", name);

    return 0;
}
