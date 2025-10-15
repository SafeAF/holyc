// ptrace single step debugger

// usage: find an address to break on
// objdump -d /bin/ls | grep main
// run with ./debugger /bin/ls 0xADDRESS

// compile programs with no pie to prevent symbol stripping
// gcc -no-pie -g -o testprog testprog.c

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void run_debuggee(const char* program) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl(program, program, NULL);
}

void run_debugger(pid_t child_pid, unsigned long addr) {
    int wait_status;
    waitpid(child_pid, &wait_status, 0);

    printf("Inserting breakpoint at %#lx\n", addr);

    long orig_data = ptrace(PTRACE_PEEKTEXT, child_pid, (void *)addr, NULL);
    if (orig_data == -1 && errno) {
        perror("PTRACE_PEEKTEXT");
        exit(1);
    }

    long breakpoint = (orig_data & ~0xFF) | 0xCC;
    ptrace(PTRACE_POKETEXT, child_pid, (void*)addr, (void*)breakpoint);

    ptrace(PTRACE_CONT, child_pid, NULL, NULL);
    waitpid(child_pid, &wait_status, 0);

    printf("Breakpoint hit!\n");

    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
    printf("RIP = %#llx\n", regs.rip);

    // Dump some registers
    printf("RAX:  0x%llx\n", regs.rax);
    printf("ORIG_RAX: 0x%llx\n", regs.orig_rax);
    printf("RCX:  0x%llx\n", regs.rcx);
    printf("RDX:  0x%llx\n", regs.rdx);
    printf("RSI:  0x%llx\n", regs.rsi);
    printf("RDI:  0x%llx\n", regs.rdi);
    printf("RBP:  0x%llx\n", regs.rbp);
    printf("RBX:  0x%llx\n", regs.rbx);

    // Restore original instruction
    ptrace(PTRACE_POKETEXT, child_pid, (void *)addr, (void *)orig_data);

    // Rewind RIP by 1 byte
    regs.rip -= 1;
    ptrace(PTRACE_SETREGS, child_pid, NULL, &regs);

    // Now loop: single-step through instructions
    char buf[16];
    while (1) {
        printf("Press ENTER to single step, or type 'q' to quit.\n");
        fgets(buf, sizeof(buf), stdin);

        if (buf[0] == 'q' || buf[0] == 'Q') {
            printf("Exiting debugger.\n");
            break;
        }

        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) == -1) {
            perror("ptrace(SINGLESTEP)");
            break;
        }

        waitpid(child_pid, &wait_status, 0);

        if (WIFEXITED(wait_status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(wait_status));
            break;
        }

        ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
        printf("RIP = %#llx\n", regs.rip);
        printf("RAX:  0x%llx\n", regs.rax);
    }
}

// setup for auto resolution of addresses for functions like main
// get base address of libc from /proc/<pid>/maps
unsigned long get_libc_base(pid_t pid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    FILE *maps = fopen(path, "r");
    if (!maps) {
        perror("fopen");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), maps)) {
        if (strstr(line, "libc") && strstr(line, "r-xp")) {
            unsigned long addr;
            sscanf(line, "%lx", &addr);
            fclose(maps);
            return addr;
        }
    }
    fclose(maps);
    fprintf(stderr, "Could not find libc base in maps\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <program> <hex_addr>\n", argv[0]);
        return 1;
    }

    char *endptr;
    unsigned long addr = strtoul(argv[2], &endptr, 16);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid address: %s\n", argv[2]);
        return 1;
    }

    pid_t child_pid = fork();
    if (child_pid == 0) {
        run_debuggee(argv[1]);
    } else {
        run_debugger(child_pid, addr);
    }

    return 0;
}
