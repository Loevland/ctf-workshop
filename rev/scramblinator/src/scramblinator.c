#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void write_to_file(char *filename, char *buffer){
    FILE *fp;
    // Write to file and add .scrambled to the extension
    char *new_filename = malloc(strlen(filename) + 11);
    strcpy(new_filename, filename);
    strcat(new_filename, ".scrambled");
    fp = fopen(new_filename, "w");
    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    fprintf(fp, "%s", buffer);
    fclose(fp);
}

void stage1(char *buffer){
    char tmp;
    int i, j;
    for (i = 0, j = strlen(buffer) - 1; i < j; i++, j--){
        tmp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmp;
    }
}

void stage2(char *buffer){
    int i;
    for (i = 0; i < strlen(buffer); i++){
        buffer[i] = buffer[i] ^ 0x55;
    }
}

void stage3(char *buffer){
    srand(0x1337);
    int i;
    for (i = 0; i < strlen(buffer); i++){
        buffer[i] = buffer[i] ^ rand();
    }
}

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: scramblinator <filename>\n");
        exit(1);
    }

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    char buffer[64] = {0};
    fgets(buffer, 64, fp);
    fclose(fp);

    stage1(buffer);
    stage2(buffer);
    stage3(buffer);
    write_to_file(argv[1], buffer);
}