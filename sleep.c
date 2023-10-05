#include <stdio.h>
#include <unistd.h>

int main() {
    int seconds = 5; // Sleep for 5 seconds
    printf("Sleeping for %d seconds...\n", seconds);
    sleep(seconds);
    printf("Awake after sleeping.\n");

    return 0;
}

