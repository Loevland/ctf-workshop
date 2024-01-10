#include <stdio.h>
#include <stdlib.h>

int 
main(void) {
    unsigned char buf[32];
    int n = 0xffeeddcc;
    int i;

    /* Printing hexadecimal memory dump from last byte of address `&n` to starting address of `buf`. */
    printf("HEXDUMP:\n|");
    for( i = sizeof(buf) + 2*sizeof(n) - 1; i >= 0; i--) {
        if((i+1) % 8 == 0) {
            printf("|\n|");
        }
        printf("%02x ", (int)buf[i]);
    }
    printf("|\n\n");
    
    /* Printing character memory dump from last byte of address `&n` to starting address of `buf`. */
    printf("CHARDUMP:\n|");
    for(i = sizeof(buf) + 2*sizeof(n) - 1; i >= 0; i--) {
        if((i+1) % 8 == 0) {
            printf("|\n|");
        }
        printf("%c ", (int)buf[i]);
    }
    printf("| \n\n");
    
    /* Writing to `buf` past its capacity to change `n`. */
    printf("PRE-WRITE:  int n := 0x%08x; \n", n);
    printf("WRITING:       &n <- 0xccddeeff; \n");
    *(int*)( buf + sizeof(buf) + 2*sizeof(n) ) = 0xccddeeff;
    printf("POST-WRITE: int n := 0x%08x; \n", n);

    return 0;
}
