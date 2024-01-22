#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    char password[22] = {0};
    char *flag = "TD{w3lc0m3_4dmin!}";

    printf("Enter the admin password: ");
    fflush(stdout);
    read(0, password, 21);

    if (!strncmp(password, "Sup3r_S3cr3t_P4ssw0rd", 21)){
        puts(flag);
    } else {
        puts("Wrong!");
    }
    return 0;
}