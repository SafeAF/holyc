// get registers

// ptrace ex
// Compile with: gcc -m64 -O0 -Wall 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

int main() {
    pid_t child = fork();

    if (child == 0) {
        // Child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP); // Pause self to let parent attach
        execl("/bin/ls", "ls", NULL);
        perror("execl");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(child, &status, 0);  // Wait for SIGSTOP

        if (WIFSTOPPED(status)) {
            printf("Child stopped, attempting to get registers...\n");

            struct user_regs_struct regs;
            if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) {
                perror("ptrace(GETREGS)");
                return 1;
            }

			printf("R15:  0x%llx\n", regs.r15);
			printf("R14:  0x%llx\n", regs.r14);
			printf("R13:  0x%llx\n", regs.r13);
			printf("R12:  0x%llx\n", regs.r12);
			printf("RBP:  0x%llx\n", regs.rbp);
			printf("RBX:  0x%llx\n", regs.rbx);
			printf("R11:  0x%llx\n", regs.r11);
			printf("R10:  0x%llx\n", regs.r10);
			printf("R9:   0x%llx\n", regs.r9);
			printf("R8:   0x%llx\n", regs.r8);
			printf("RAX:  0x%llx\n", regs.rax);
			printf("RCX:  0x%llx\n", regs.rcx);
			printf("RDX:  0x%llx\n", regs.rdx);
			printf("RSI:  0x%llx\n", regs.rsi);
			printf("RDI:  0x%llx\n", regs.rdi);
			printf("ORIG_RAX: 0x%llx\n", regs.orig_rax);
			printf("RIP:  0x%llx\n", regs.rip);
			printf("CS:   0x%llx\n", regs.cs);
			printf("EFLAGS: 0x%llx\n", regs.eflags);
			printf("RSP:  0x%llx\n", regs.rsp);
			printf("SS:   0x%llx\n", regs.ss);
			printf("FS_BASE: 0x%llx\n", regs.fs_base);
			printf("GS_BASE: 0x%llx\n", regs.gs_base);
			printf("DS:   0x%llx\n", regs.ds);
			printf("ES:   0x%llx\n", regs.es);
			printf("FS:   0x%llx\n", regs.fs);
			printf("GS:   0x%llx\n", regs.gs);
            ptrace(PTRACE_CONT, child, NULL, NULL);
            waitpid(child, &status, 0);  // Wait for it to finish
            tcsetpgrp(STDIN_FILENO, getpgrp());
        } else {
            fprintf(stderr, "Unexpected stop status\n");
        }
    }

    return 0;
}

