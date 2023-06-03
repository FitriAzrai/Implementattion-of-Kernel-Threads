#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

void new_thread(void *arg1, void *arg2)
{
    printf("New thread: arg1=%p, arg2=%p\n", arg1, arg2);
    // Perform thread-specific tasks here
    // ...
}

int main()
{
    void *arg1 = NULL;
    void *arg2 = NULL;
    void *stack = malloc(4096); // Allocate memory for the stack

    pid_t tid = syscall(SYS_clone, new_thread, arg1, arg2, stack);
    if (tid > 0)
    {
        printf("Created new thread with thread ID: %d\n", tid);
        // Perform main thread tasks here
        // ...
    }
    else
    {
        printf("Failed to create new thread\n");
        free(stack);
        return 1;
    }

    // Wait for the new thread to complete (optional)
    // ...

    free(stack);
    return 0;
}
