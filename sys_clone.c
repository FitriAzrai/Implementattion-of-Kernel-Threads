#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>

asmlinkage long sys_clone(void (*fcn)(void *, void *), void *arg1, void *arg2, void *stack)
{
    struct task_struct *p;
    int pid;

    // Allocate a new task_struct for the new thread
    p = alloc_task_struct();
    if (!p)
        return -ENOMEM;

    // Set up the new thread's stack
    p->stack = stack;
    p->stack_size = 4096; // Initial stack size = 4KB

    // Copy the arguments to the new thread's stack
    *(void **)(p->stack) = arg1;
    *(void **)(p->stack + sizeof(void *)) = arg2;

    // Set up the new thread's initial stack frame
    p->thread.ip = (unsigned long)fcn;
    p->thread.sp = (unsigned long)(p->stack + p->stack_size - sizeof(unsigned long));

    // Set the necessary thread attributes (e.g., scheduling priority)
    // You can modify this according to your requirements

    // Add the new thread to the scheduler's ready queue
    pid = do_fork(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0, NULL, NULL, p);
    if (pid < 0)
    {
        free_task_struct(p);
        return pid;
    }

    return pid; // Return the thread ID of the new thread
}
