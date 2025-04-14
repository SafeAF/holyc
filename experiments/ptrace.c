// ptrace ex
// Compile with: gcc -m64 -O0 -Wall -o ptrace_debugger ptrace_debugger.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h> // for user_regs_struct
#include <errno.h>

int main() {
    pid_t child = fork();

    if (child == 0) {
        // Child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL); // allow tracing
        execl("/bin/ls", "ls", NULL); // run some trivial program
        perror("execl");
        exit(1);
    } else {
        // Parent (debugger)
        int status;
        waitpid(child, &status, 0); // wait for child to stop on exec

        if (WIFEXITED(status)) {
            printf("Child exited prematurely.\n");
            return 1;
        }

        struct user_regs_struct regs;

        // Read registers
        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) {
            perror("ptrace(GETREGS)");
            return 1;
        }

#if __x86_64__
        printf("RIP (Instruction Pointer): 0x%llx\n", regs.rip);
#else
        printf("EIP (Instruction Pointer): 0x%lx\n", regs.eip);
#endif

        // Continue execution
        ptrace(PTRACE_CONT, child, NULL, NULL);

        // Wait for child to finish
        waitpid(child, &status, 0);
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
