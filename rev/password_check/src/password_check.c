#include <stdio.h>
#include <string.h>
#include <unistd.h>


int check_password(char *password){
    if (strlen(password) != 32){
        return 0;
    }

    if (strncmp(password, "TD{youw", 7) != 0){
        return 0;
    }

    if (strncmp(password+7, "illno", 5) != 0){
        return 0;
    }

    if (strncmp(password+12, "tguess", 6) != 0){
        return 0;
    }

    if (strncmp(password+22, "password!}", 10) != 0){
        return 0;
    }

    if (strncmp(password+18, "this", 4) != 0){
        return 0;
    }
    return 1;
}

int main(){
    char password[32] = {0};

    printf("Enter the password: ");
    fflush(stdout);
    read(0, password, 32);

    if (check_password(password)){
        printf("Correct!\n");
    } else {
        printf("Wrong!\n");
    }

    return 0;
}