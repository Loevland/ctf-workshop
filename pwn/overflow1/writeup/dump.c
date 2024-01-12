#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return nearest value of `n` in positive direction. */
void *
roundup8(void *n) {
    return (void *)((long long)(n + 7) & ~7);
}

/* Return 1 if `target <= v <= target+offset`, 0 otherwise. */
int
isin8byterange(void *v, void *target) {
    return (target <= v) && (v <= target+0x8);
}

void 
cleanchars(char *s, int n) {
    char *c = s;
    while(c < s+n) {
        if(!isprint(*c)) {
            *c = '.';
        }
        c++;
    }
    return;
}

int 
main(void) {
    int n = 0xffeeddcc;
    unsigned char *addr;
    unsigned char buf[32] = "trats                       dne";
    unsigned char fmt[512], byte[8+1];
    char memaddr[64], variable[64];

    /* Printing hexadecimal memory dump from last byte of address `&n` to starting address of `buf`. */
    printf("---------------------------------------------------------------------\n");
    printf("| %14s | %14s%9s | %15s |\n", "Memory Address", "HEXDUMP", "", "Variable (not aligned)");
    printf("---------------------------------------------------------------------\n");
    for(addr = roundup8(&n+sizeof(n))-1; addr > buf-8; addr -= 8) {
        /* Memory Address. */
        snprintf(memaddr, sizeof(memaddr), "%p", addr+1);
        /* HEXDUMP. */
        memcpy(byte, addr, 8);
        /* Variable. */
        if( isin8byterange(addr, &n) ) {
            snprintf(variable, sizeof(memaddr), "&n = %p", &n);
        } else if( isin8byterange(addr, &addr) ) {
            snprintf(variable, sizeof(memaddr), "&addr = %p", &addr);
        } else if( isin8byterange(addr, &buf) ) {
            snprintf(variable, sizeof(memaddr), "&buf = %p", &buf);
        } else {
            variable[0] = '\0';
        }
        /* Format hex line. */
        snprintf(fmt, sizeof(fmt),
            "| %14s | %02x %02x %02x %02x %02x %02x %02x %02x | %22s |",
            memaddr, byte[7], byte[6], byte[5], byte[4], byte[3], byte[2], byte[1], byte[0], variable
        );
        /* 8-byte hexdump line. */
        printf("%s\n", fmt);
    }
    printf("---------------------------------------------------------------------\n");

    printf("\n");

    /* Printing character memory dump from last byte of address `&n` to starting address of `buf`. */
    printf("---------------------------------------------------------------------\n");
    printf("| %14s | %14s%1s | %15s |\n", "Memory Address", "CHARDUMP ('.' no char)", "", "Variable (not aligned)");
    printf("---------------------------------------------------------------------\n");
    for(addr = roundup8(&n+sizeof(n))-1; addr > buf-8; addr -= 8) {
        /* Memory Address. */
        snprintf(memaddr, sizeof(memaddr), "%p", addr+1);
        /* CHARDUMP. */
        memcpy(byte, addr, 8);
        cleanchars(byte, 8);
        byte[8] = '\0';
        /* Variable. */
        if( isin8byterange(addr, &n) ) {
            snprintf(variable, sizeof(memaddr), "&n = %p", &n);
        } else if( isin8byterange(addr, &addr) ) {
            snprintf(variable, sizeof(memaddr), "&addr = %p", &addr);
        } else if( isin8byterange(addr, &buf) ) {
            snprintf(variable, sizeof(memaddr), "&buf = %p", &buf);
        } else {
            variable[0] = '\0';
        }
        /* Format hex line. */
        snprintf(fmt, sizeof(fmt),
            "| %14s | %2c %2c %2c %2c %2c %2c %2c %2c | %22s |",
            memaddr, byte[7], byte[6], byte[5], byte[4], byte[3], byte[2], byte[1], byte[0], variable
        );
        /* 8-byte chardump line. */
        printf("%s\n", fmt);
    }
    printf("---------------------------------------------------------------------\n");
    
    printf("\n");
    
    /* Writing to `buf` past its capacity to change `n`. */
    printf("PRE-WRITE:                int n := 0x%08x; \n", n);
    printf("WRITING TO: buf+offset, i.e. &n <- 0xccddeeff; \n");
    *(int*)( buf + sizeof(buf) + sizeof(addr) + sizeof(n) ) = 0xccddeeff;
    printf("POST-WRITE:               int n := 0x%08x; \n", n);

    return 0;
}
