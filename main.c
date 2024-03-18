#include <stdio.h>
#include <unistd.h>

int main() {
    char new_path[20]; // Assuming maximum path length is 100 characters
    
    printf("new path: ");
    scanf("%s", new_path);
    
    // Change directory to the new path
    if (chdir(new_path) == 0) {
        printf("Directory changed to: %s\n", new_path);
    } else {
        printf("change directory to: %s\n", new_path);
    }
    
    return 0;
}
