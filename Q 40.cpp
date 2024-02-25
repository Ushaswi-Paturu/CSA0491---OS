#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *filename = "myfile.txt"; // Example filename
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Example permissions: read for owner, write for owner, read for group and others

    // Change file permissions
    if (chmod(filename, permissions) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("Error in changing file permissions");
        return 1;
    }

    return 0;
}

