#include <stdio.h> // For printf
#include <unistd.h> // For getcwd, chdir
#include <stdlib.h> // For malloc, free

int main() {
    // Get the current working directory
    size_t buffer_size = 256; // Buffer size for directory path
    char *current_dir = (char *)malloc(buffer_size); // Allocate memory for buffer

    if (getcwd(current_dir, buffer_size) == NULL) {
        perror("Error getting current directory");
        free(current_dir); // Free allocated memory
        return 1;
    }

    printf("Current directory: %s\n", current_dir);

    // Change to a different directory (e.g., /tmp)
    if (chdir("/") != 0) {
        perror("Error changing directory");
        free(current_dir); // Free allocated memory
        return 1;
    }

    // Get the new current working directory
    if (getcwd(current_dir, buffer_size) == NULL) {
        perror("Error getting new directory");
        free(current_dir); // Free allocated memory
        return 1;
    }

    printf("Changed to directory: %s\n", current_dir);

    free(current_dir); // Free allocated memory
    return 0;
}
