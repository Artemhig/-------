#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char* generate_password(int length) {
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* password = malloc(length + 1);
    
    int urandom = open("/dev/urandom", O_RDONLY);
    unsigned char random_bytes[length];
    read(urandom, random_bytes, length);
    close(urandom);
    
    for (int i = 0; i < length; i++) {
        password[i] = charset[random_bytes[i] % 62];
    }
    password[length] = '\0';
    return password;
}

int main(int argc, char *argv[]) {
    int num_passwords = atoi(argv[1]);
    int password_length = atoi(argv[2]);
    
    for (int i = 0; i < num_passwords; i++) {
        char* password = generate_password(password_length);
        printf("%s\n", password);
        free(password);
    }
    
    return 0;
}