#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libc.h"

int main()
{
    int *a = malloc(sizeof(int));
    *a = 0;
    int pid = fork();
    if (pid == 0)
    {
        (*a)+= 1;
        exit(1);
    }
    wait(NULL);
    printf("%d\n", *a);
}
